/*
 * event.h - libevent compatible event loop.
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

#ifndef _USUAL_EVENT_H_
#define _USUAL_EVENT_H_

#include <sys/time.h>

#include <usual/aatree.h>
#include <usual/list.h>
#include <usual/time.h>

/*
 * Flags for event_set() / event_assign():
 *   EV_READ, EV_WRITE, EV_SIGNAL, EV_PERSIST
 *
 * Flags given to user callback:
 *   EV_READ, EV_WRITE, EV_SIGNAL, EV_TIMEOUT.
 */
enum EventFlags {
	EV_TIMEOUT = 1,
	EV_READ = 2,
	EV_WRITE = 4,
	EV_SIGNAL = 8,
	EV_PERSIST = 16,
};

/* Flags for event_loop() */
enum EventLoopType {
	EVLOOP_ONCE = 1,
	EVLOOP_NONBLOCK = 2,
};

/* event_base contents are not open */
struct event_base;

/* user callback signature */
typedef void (*uevent_cb_f)(int fd, short flags, void *arg);

/* macros to read fd and signal values */
#define EVENT_FD(ev) ((ev)->fd)
#define EVENT_SIGNAL(ev) ((ev)->fd)

/*
 * Our event structure.
 *
 * Although the struct is open, no direct accesses should be done.
 * Thus also the fields are incompat with libevent.
 */
struct event {
	/* node for fd or signal lists */
	struct List node;

	/* timeout info */
	usec_t timeout_val;
	struct AANode timeout_node;

	/* back-pointer into pollfd list */
	int ev_idx;

	/* event base it is attached to */
	struct event_base *base;

	/* user callback */
	uevent_cb_f cb_func;
	void *cb_arg;

	/* fd or signal */
	int fd;

	/* both user and internal flags */
	short flags;
};

struct event_base *event_init(void) _MUSTCHECK;
void event_base_free(struct event_base *base);

void event_set(struct event *ev, int fd, short flags, uevent_cb_f cb, void *arg);
int event_loop(int loop_flags) _MUSTCHECK;
int event_loopbreak(void);

int event_add(struct event *ev, struct timeval *timeout) _MUSTCHECK;
int event_del(struct event *ev);

void event_assign(struct event *ev, struct event_base *base,
		  int fd, short flags, uevent_cb_f cb, void *cb_arg);

int event_base_loop(struct event_base *base, int loop_flags) _MUSTCHECK;
int event_base_loopbreak(struct event_base *base);

#define evtimer_set(ev, cb, arg) event_set(ev, -1, 0, cb, arg)
#define evtimer_add(ev, tv) event_add(ev, tv)

#define signal_set(ev, sig, cb, arg) event_set(ev, sig, EV_SIGNAL | EV_PERSIST, cb, arg)
#define signal_add(ev, tv) event_add(ev, tv)

/* random compat */
int event_once(int fd, short flags, uevent_cb_f cb_func, void *cb_arg, struct timeval *timeout);
int event_base_once(struct event_base *base, int fd, short flags, uevent_cb_f cb_func, void *cb_arg, struct timeval *timeout);
int event_loopexit(struct timeval *timeout);
int event_base_loopexit(struct event_base *base, struct timeval *timeout);
int event_base_set(struct event_base *base, struct event *ev);

/* pointless compat */
#define event_dispatch() event_loop(0)
#define event_base_dispatch(base) event_base_loop(base, 0)
#define event_initialized(ev) is_event_active(ev)
#define signal_initialized(ev) is_event_active(ev)
#define evtimer_initialized(ev) is_event_active(ev)
int is_event_active(struct event *ev);

#endif

