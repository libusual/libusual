/*
 * event.c - libevent compatible event loop.
 *
 * Copyright (c) 2009 Marko Kreen
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */ 

/*
 * Small poll()-based async event loop, API-compatible with libevent.
 *
 * For sitations where full libevent is not necessary.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <usual/event.h>

#include <sys/socket.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>

#include <usual/statlist.h>
#include <usual/socket.h>
#include <usual/alloc.h>

/* max number of signals we care about */
#define MAX_SIGNAL 32

/* if tv_sec is larger, it's absolute timeout */
#define MAX_REL_TIMEOUT (30*24*60*60)

/* if no nearby timeouts, how many seconds to sleep */
#define MAX_SLEEP 5

/* extra event flag to track if event is added */
#define EV_ACTIVE 0x80

struct event_base {
	struct AATree timeout_tree;

	struct StatList fd_list;
	struct event **pfd_event;
	struct pollfd *pfd_list;
	int pfd_size;

	bool loop_break;
	bool loop_exit;

	/* signal handling */
	struct List sig_node;
	struct List sig_waiters[MAX_SIGNAL];
	int sig_send, sig_recv;
	struct event sig_ev;
	unsigned int sig_seen[MAX_SIGNAL];
};

/* default event base */
static struct event_base *current_base = NULL;

/* global signal data */
static volatile unsigned int sig_count[MAX_SIGNAL];
static bool signal_set_up[MAX_SIGNAL];
static struct sigaction old_handler[MAX_SIGNAL];
static LIST(sig_base_list);


static bool sig_init(struct event_base *base, int sig);
static void sig_close(struct event_base *base);

/*
 * Debugging.
 */

#ifdef CASSERT
#include <usual/logging.h>
#include <usual/time.h>
#include <stdarg.h>
#include <stdio.h>
static void base_dbg(struct event_base *base, const char *s, ...)
{
	va_list ap;
	char buf[1024];

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	log_noise("event base=%p: fdlist=%u timeouts=%d pfds=%d: %s",
	       base, statlist_count(&base->fd_list),
	       base->timeout_tree.count,
	       base->pfd_size, buf);
}

static void ev_dbg(struct event *ev, const char *s, ...)
{
	va_list ap;
	char buf[1024], tval[128];
	const char *typ = (ev->flags & EV_SIGNAL) ? "sig" : "fd";

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	log_noise("event %s %d (flags=%s%s%s%s%s) [%s]: %s", typ, ev->fd,
	       (ev->flags & EV_ACTIVE) ? "A" : "",
	       (ev->flags & EV_PERSIST) ? "P" : "",
	       (ev->flags & EV_TIMEOUT) ? "T" : "",
	       (ev->flags & EV_READ) ? "R" : "",
	       (ev->flags & EV_WRITE) ? "W" : "",
	       (ev->flags & EV_TIMEOUT)
	       ? format_time_ms(&ev->timeout, tval, sizeof(tval))
	       : "-",
	       buf);
}
#else
#define base_dbg(b, ...)
#define ev_dbg(b, ...)
#endif

/*
 * Helper functions.
 */

/* convert user tv to absolute tv */
static void fill_timeout(struct timeval *dst, struct timeval *tv)
{
	if (tv->tv_sec < MAX_REL_TIMEOUT) {
		struct timeval now;
		gettimeofday(&now, NULL);
		timeradd(&now, tv, dst);
	} else {
		*dst = *tv;
	}
}

/* compare timevals */
static int cmp_tv(struct timeval *tv1, struct timeval *tv2)
{
	if (tv1->tv_sec == tv2->tv_sec) {
		if (tv1->tv_usec == tv2->tv_usec)
			return 0;
		return (tv1->tv_usec < tv2->tv_usec) ? -1 : 1;
	} else {
		return (tv1->tv_sec < tv2->tv_sec) ? -1 : 1;
	}

}

/* compare events by their timeouts */
static int cmp_timeout(long item, struct AANode *n1)
{
	struct AANode *n0 = (void *)item;
	struct event *ev0 = container_of(n0, struct event, timeout_node);
	struct event *ev1 = container_of(n1, struct event, timeout_node);
	int res = cmp_tv(&ev0->timeout, &ev1->timeout);
	if (res != 0)
		return res;
	/* compare pointers, to make same timeouts inequal */
	if (ev0 == ev1)
		return 0;
	return (ev0 < ev1) ? -1 : 1;
}

/* enlarge pollfd array if needed */
static bool make_room(struct event_base *base, int need)
{
	int total;
	void *tmp1;
	void *tmp2;

	if (need < base->pfd_size)
		return true;

	total = base->pfd_size * 2;
	if (total < 8) total = 8;
	while (total < need)
		total *= 2;

	tmp1 = realloc(base->pfd_list, total * sizeof(struct pollfd));
	if (!tmp1)
		return false;
	base->pfd_list = tmp1;

	tmp2 = realloc(base->pfd_event, total * sizeof(struct event *));
	if (!tmp2)
		return false;
	base->pfd_event = tmp2;

	base->pfd_size = total;
	return true;
}

/*
 * Single base functions.
 */

int event_loop(int loop_flags)
{
	return event_base_loop(current_base, loop_flags);
}

int event_loopbreak(void)
{
	return event_base_loopbreak(current_base);
}

void event_set(struct event *ev, int fd, short flags, uevent_cb_f cb, void *arg)
{
	event_assign(ev, current_base, fd, flags, cb, arg);
}

int event_once(int fd, short flags, uevent_cb_f cb_func, void *cb_arg, struct timeval *timeout)
{
	return event_base_once(current_base, fd, flags, cb_func, cb_arg, timeout);
}

int event_loopexit(struct timeval *timeout)
{
	return event_base_loopexit(current_base, timeout);
}

/*
 * Event base initialization.
 */

struct event_base *event_init(void)
{
	struct event_base *base;
	int i;

	base = calloc(1, sizeof(*base));

	/* initialize timeout and fd areas */
	aatree_init(&base->timeout_tree, cmp_timeout, NULL);
	statlist_init(&base->fd_list, "fd_list");

	/* initialize signal areas */
	for (i = 0; i < MAX_SIGNAL; i++)
		list_init(&base->sig_waiters[i]);
	list_init(&base->sig_node);
	base->sig_send = base->sig_recv = -1;

	/* allocate pollfds */
	if (!make_room(base, 8)) {
		event_base_free(base);
		return NULL;
	}

	if (!current_base)
		current_base = base;
	return base;
}

void event_base_free(struct event_base *base)
{
	if (!base) {
		if (!current_base)
			return;
		base = current_base;
	}
	if (base == current_base)
		current_base = NULL;
	free(base->pfd_event);
	free(base->pfd_list);
	sig_close(base);
	free(base);
}

int event_base_loopbreak(struct event_base *base)
{
	base->loop_break = true;
	return 0;
}

/*
 * Multi-base functions.
 */

void event_assign(struct event *ev, struct event_base *base, int fd, short flags, uevent_cb_f cb, void *arg)
{
	Assert(base);
	Assert((ev->flags & EV_ACTIVE) == 0);

	ev->fd = fd;
	ev->base = base;
	ev->flags = flags;
	ev->cb_func = cb;
	ev->cb_arg = arg;
	ev->ev_idx = -1;
	list_init(&ev->node);
	ev_dbg(ev, "event_set");
}

int event_del(struct event *ev)
{
	struct event_base *base = ev->base;

	/* allow repeated deletions */
	if ((ev->flags & EV_ACTIVE) == 0) {
		ev_dbg(ev, "event_del for inactive event??");
		return 0;
	}
	ev_dbg(ev, "event_del");

	/* remove from fd/signal list */
	if (ev->flags & EV_SIGNAL)
		list_del(&ev->node);
	else if (ev->flags & (EV_READ | EV_WRITE))
		statlist_remove(&base->fd_list, &ev->node);

	/* remove from timeout tree */
	if (ev->flags & EV_TIMEOUT) {
		aatree_remove(&ev->base->timeout_tree, (long)&ev->timeout_node);
		ev->flags &= ~EV_TIMEOUT;
	}

	/* clear reference to pollfd area */
	if (ev->ev_idx >= 0) {
		ev->base->pfd_event[ev->ev_idx] = NULL;
		ev->ev_idx = -1;
	}

	/* tag inactive */
	ev->flags &= ~EV_ACTIVE;

	return 0;
}


/* handles only relarive timeouts */
int event_add(struct event *ev, struct timeval *timeout)
{
	struct event_base *base = ev->base;

	Assert((ev->flags & EV_ACTIVE) == 0);
	Assert(base);

	/* timeout sanity check, but dont use it yet */
	if (timeout) {
		if (ev->flags & EV_PERSIST) {
			errno = EINVAL;
			return -1;
		}
	} else if (ev->flags & EV_TIMEOUT) {
		ev->flags &= ~EV_TIMEOUT;
	}

	/* setup signal/fd */
	if (ev->flags & EV_SIGNAL) {
		if (ev->flags & (EV_READ|EV_WRITE)) {
			errno = EINVAL;
			return -1;
		}
		if (!sig_init(base, ev->fd))
			return -1;
		list_append(&base->sig_waiters[ev->fd], &ev->node);
	} else if (ev->flags & (EV_READ|EV_WRITE)) {
		statlist_append(&base->fd_list, &ev->node);
	}

	/* now act on timeout */
	if (timeout) {
		fill_timeout(&ev->timeout, timeout);
		ev->flags |= EV_TIMEOUT;
		aatree_insert(&base->timeout_tree, (long)&ev->timeout_node, &ev->timeout_node);
	}
	ev->ev_idx = -1;
	ev->flags |= EV_ACTIVE;

	ev_dbg(ev, "event_add");

	return 0;
}

/*
 * Event loop functions.
 */

static void deliver_event(struct event *ev, short flags)
{
	ev_dbg(ev, "deliver_event: %d", flags);

	/* remove non-persitant event before calling user func */
	if ((ev->flags & EV_PERSIST) == 0)
		event_del(ev);

	/* now call user func */
	ev->cb_func(ev->fd, flags, ev->cb_arg);
}

static inline struct event *get_smallest_timeout(struct event_base *base)
{
	struct AANode *node = base->timeout_tree.root;
	struct AANode *first = NULL;
	struct event *ev;

	while (!aatree_is_nil_node(node)) {
		first = node;
		node = node->left;
	}
	if (first) {
		ev = container_of(first, struct event, timeout_node);
		return ev;
	}
	return NULL;
}

static int calc_timeout(struct event_base *base)
{
	struct event *ev;
	int res, secs, usecs;
	struct timeval now;

	ev = get_smallest_timeout(base);
	if (!ev)
		return MAX_SLEEP * 1000;

	gettimeofday(&now, NULL);

	if (now.tv_sec + MAX_SLEEP < ev->timeout.tv_sec)
		return MAX_SLEEP * 1000;
	if (ev->timeout.tv_sec < now.tv_sec)
		return 0;

	secs = ev->timeout.tv_sec - now.tv_sec;
	usecs = ev->timeout.tv_usec - now.tv_usec;
	if (usecs < 0) {
		secs--;
		usecs += 1000000;
	}
	res = (secs * 1000) + ((usecs + 999) / 1000);
	if (res < 0)
		return 0;
	return res;
}

static void process_fds(struct event_base *base, int pf_cnt)
{
	int i;

	for (i = 0; i < pf_cnt; i++) {
		struct pollfd *pf = &base->pfd_list[i];
		struct event *ev = base->pfd_event[i];
		if (!ev)
			continue;
		base->pfd_event[i] = NULL;
		ev->ev_idx = -1; // is it needed?
		if (pf->revents & (POLLIN | POLLOUT | POLLERR | POLLHUP)) {
			int flags = ev->flags & (EV_READ | EV_WRITE);
			deliver_event(ev, flags);
		}
		if (base->loop_break)
			break;
	}
}

static void process_timeouts(struct event_base *base)
{
	struct timeval now;
	struct event *ev;

	ev = get_smallest_timeout(base);
	if (!ev)
		return;

	gettimeofday(&now, NULL);

	while (ev) {
		if (timercmp(&now, &ev->timeout, <))
			break;
		deliver_event(ev, EV_TIMEOUT);
		if (base->loop_break)
			break;
		ev = get_smallest_timeout(base);
	}
}

int event_base_loop(struct event_base *base, int loop_flags)
{
	int pf_cnt, res, timeout_ms;
	struct List *node;

	/* don't loop if non-block was requested */
	if (loop_flags & EVLOOP_NONBLOCK)
		loop_flags |= EVLOOP_ONCE;

	base->loop_break = false;
	base->loop_exit = false;
loop:
	if (!make_room(base, statlist_count(&base->fd_list)))
		return -1;

	pf_cnt = 0;
	statlist_for_each(node, &base->fd_list) {
		struct event *ev = container_of(node, struct event, node);
		struct pollfd *pf;

		ev->ev_idx = pf_cnt++;
		base->pfd_event[ev->ev_idx] = ev;
		pf = &base->pfd_list[ev->ev_idx];

		pf->events = 0;
		pf->revents = 0;
		pf->fd = ev->fd;
		if (ev->flags & EV_READ)
			pf->events |= POLLIN;
		if (ev->flags & EV_WRITE)
			pf->events |= POLLOUT;
	}

	if (loop_flags & EVLOOP_NONBLOCK)
		timeout_ms = 0;
	else
		timeout_ms = calc_timeout(base);

	res = poll(base->pfd_list, pf_cnt, timeout_ms);
	base_dbg(base, "poll(%d, timeout=%d) = res=%d errno=%d",
		 pf_cnt, timeout_ms, res, res < 0 ? errno : 0);

	if (res == -1 && errno != EINTR)
		return -1;

	if (res > 0) {
		process_fds(base, pf_cnt);
		if (base->loop_break)
			return 0;
	}

	process_timeouts(base);

	if (base->loop_break)
		return 0;

	if (loop_flags & EVLOOP_ONCE)
		return 0;

	if (base->loop_exit)
		return 0;

	goto loop;
}

/*
 * Signal handling.
 */

/* global signal handler registered via sigaction() */
static void uevent_sig_handler(int sig, siginfo_t *si, void *arg)
{
	struct List *node, *tmp;
	struct event_base *base;
	uint8_t byte = sig;
	int res;

	if (sig < 0 || sig >= MAX_SIGNAL)
		return;
	sig_count[sig]++;

	list_for_each_safe(node, &sig_base_list, tmp) {
		base = container_of(node, struct event_base, sig_node);
		if (base->sig_send >= 0) {
		loop:
			res = send(base->sig_send, &byte, 1, MSG_NOSIGNAL);
			if (res == -1 && (errno == EINTR))
				goto loop;
		}
	}
}

/* close signal resources on one base */
static void sig_close(struct event_base *base)
{
	list_del(&base->sig_node);
	if (base->sig_send >= 0)
		close(base->sig_send);
	if (base->sig_recv >= 0)
		close(base->sig_recv);
	base->sig_recv = base->sig_send = -1;
}

/* call all handlers waiting for specific signal */
static void deliver_signal(struct event_base *base, int sig)
{
	struct List *node, *tmp;

	list_for_each_safe(node, &base->sig_waiters[sig], tmp) {
		struct event *ev = container_of(node, struct event, node);
		deliver_event(ev, EV_SIGNAL);
	}
}

/* reader from sig socket, calls actual signal handlers */
static void sig_reader(int fd, short flags, void *arg)
{
	struct event_base *base = arg;
	uint8_t buf[128];
	int res, sig;

	/* drain the socket */
loop:
	res = recv(fd, buf, sizeof(buf), 0);
	if (res < 0) {
		if (errno == EINTR)
			goto loop;
		if (errno != EAGAIN)
			goto some_error;
	} else if (res == 0)
		goto some_error;

	/* now check for new signals */
	for (sig = 0; sig < MAX_SIGNAL; sig++) {
		unsigned glob, local;
		if (list_empty(&base->sig_waiters[sig]))
			continue;
		glob = sig_count[sig];
		local = base->sig_seen[sig];
		if (glob != local) {
			base->sig_seen[sig] = glob;
			deliver_signal(base, sig);
		}
	}
	return;

some_error:
	//log_warning("signal reading got error: res=%d err=%s", res, strerror(errno));
	sig_close(base);
}

static bool sig_init(struct event_base *base, int sig)
{
	int spair[2];

	if (sig < 0 || sig >= MAX_SIGNAL) {
		errno = EINVAL;
		return false;
	}

	/* global handler setup */
	if (!signal_set_up[sig]) {
		struct sigaction sa;
		memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = uevent_sig_handler;
		sa.sa_flags = SA_SIGINFO | SA_RESTART;
		if (sigaction(sig, &sa, &old_handler[sig]) != 0)
			return false;
	}

	/* local handler for base */
	if (list_empty(&base->sig_node)) {
		if (socketpair(AF_UNIX, SOCK_STREAM, 0, spair) != 0)
			return false;
		if (!socket_setup(spair[0], true))
			goto failed;
		if (!socket_setup(spair[1], true))
			goto failed;
		event_assign(&base->sig_ev, base, spair[1], EV_READ|EV_PERSIST, sig_reader, base);
		if (event_add(&base->sig_ev, NULL) != 0)
			goto failed;
		base->sig_send = spair[0];
		base->sig_recv = spair[1];
		list_append(&sig_base_list, &base->sig_node);
	}

	/* if first waiter, then ignore previous signals */
	if (list_empty(&base->sig_waiters[sig]))
		base->sig_seen[sig] = sig_count[sig];
	return true;

failed:
	close(spair[0]);
	close(spair[1]);
	return false;
}

/*
 * One-time events.
 */

struct once_event {
	struct event ev;
	uevent_cb_f cb_func;
	void *cb_arg;
};

static void once_handler(int fd, short flags, void *arg)
{
	struct once_event *once = arg;
	uevent_cb_f cb_func = once->cb_func;
	void *cb_arg = once->cb_arg;

	free(once);
	cb_func(fd, flags, cb_arg);
}

int event_base_once(struct event_base *base, int fd, short flags,
		    uevent_cb_f cb_func, void *cb_arg,
		    struct timeval *timeout)
{
	struct once_event *once;

	if (flags & EV_PERSIST) {
		errno = EINVAL;
		return -1;
	}

	once = zmalloc(sizeof(*once));
	if (!once)
		return -1;

	event_assign(&once->ev, base, fd, flags, once_handler, once);
	if (event_add(&once->ev, timeout) != 0) {
		free(once);
		return -1;
	}
	return 0;
}

static void loopexit_handler(int fd, short flags, void *arg)
{
	struct event_base *base = arg;
	base->loop_exit = true;
}

int event_base_loopexit(struct event_base *base, struct timeval *timeout)
{
	return event_base_once(base, -1, 0, loopexit_handler, base, timeout);
}

int event_base_set(struct event_base *base, struct event *ev)
{
	if (ev->flags & EV_ACTIVE) {
		errno = EINVAL;
		return -1;
	}
	ev->base = base;
	return 0;
}

/*
 * Is activated.
 */

int is_event_initialized(struct event *ev)
{
	return (ev->flags & EV_ACTIVE) ? 1 : 0;
}

