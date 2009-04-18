
#include <usual/compat.h>

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#ifdef HAVE_UCRED_H
#include <ucred.h>
#endif
#ifdef HAVE_SYS_UCRED_H
#include <sys/ucred.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_SYS_UN_H
#include <sys/un.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_NETINET_TCP_H
#include <netinet/tcp.h>
#endif

#include <usual/logging.h>

#ifndef HAVE_GETLINE
/*
 * Read line from FILE with dynamic allocation.
 */
int getline(char **line_p, size_t *size_p, void *_f)
{
	FILE *f = _f;
	char *p;
	int len = 0;

	if (!*line_p || *size_p < 128) {
		p = realloc(*line_p, 512);
		if (!p) return -1;
		*line_p = p;
		*size_p = 512;
	}

	while (1) {
		p = fgets(*line_p + len, *size_p - len, f);
		if (!p)
			return len ? len : -1;
		len += strlen(p);
		if ((*line_p)[len - 1] == '\n')
			return len;
		p = realloc(*line_p, *size_p * 2);
		if (!p)
			return -1;
		*line_p = p;
		*size_p *= 2;
	}
}
#endif

#ifndef HAVE_GETPEEREID
/*
 * Get other side's uid for UNIX socket.
 *
 * Standardise on getpeereid() from BSDs.
 */
int getpeereid(int fd, uid_t *uid_p, gid_t *gid_p)
{
#ifdef SO_PEERCRED
	struct ucred cred;
	socklen_t len = sizeof(cred);
	if (getsockopt(fd, SOL_SOCKET, SO_PEERCRED, &cred, &len) >= 0) {
		*uid_p = cred.uid;
		*gid_p = cred.gid;
		return 0;
	}
#else /* !SO_PEERCRED */
#ifdef HAVE_GETPEERUCRED
	ucred_t *cred = NULL;
	if (getpeerucred(fd, &cred) >= 0) {
		*uid_p = ucred_geteuid(cred);
		*gid_p = ucred_getegid(cred);
		ucred_free(cred);
		if (*uid_p >= 0 && *gid_p >= 0)
			return 0;
	}
#else
	errno = ENOSYS;
#endif /* HAVE_GETPEERUCRED */
#endif /* !SO_PEERCRED */
	return -1;
}
#endif

#ifndef HAVE_BASENAME
const char *basename(const char *path)
{
	const char *p;
	if (path == NULL || path[0] == 0)
		return ".";
	if ((p = strrchr(path, '/')) != NULL)
		return p[1] ? p + 1 : p;
	return path;
}
#endif

#ifndef HAVE_INET_NTOP
const char *inet_ntop(int af, const void *src, char *dst, int cnt)
{
	const unsigned char *p = src;
	if (af != AF_INET)
		return NULL;
	snprintf(dst, cnt, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return dst;
}
#endif

#ifndef HAVE_POLL
/*
 * Emulate poll() with select()
 */
#include <sys/time.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

/*
 * dynamic buffer for fd_set to avoid depending on FD_SETSIZE
 */

struct fd_buf {
	fd_set *set;
	int alloc_bytes;
};

static void fdbuf_zero(struct fd_buf *buf)
{
	if (buf->set)
		memset(buf->set, 0, buf->alloc_bytes);
}

static bool fdbuf_resize(struct fd_buf *buf, int fd)
{
	/* get some extra room for quaranteed alignment */
	int need_bytes = fd/8 + 32;
	/* default - 2048 fds */
	int alloc = 256;
	unsigned char *ptr;

	if (buf->alloc_bytes < need_bytes)
	{
		while (alloc < need_bytes)
			alloc *= 2;

		if (!buf->set)
			ptr = malloc(alloc);
		else
			ptr = realloc(buf->set, alloc);

		if (!ptr)
			return false;

		/* clean new area */
		memset(ptr + buf->alloc_bytes, 0, alloc - buf->alloc_bytes);

		buf->set = (fd_set *)ptr;
		buf->alloc_bytes = alloc;
	}
	return true;
}

int poll(struct pollfd *fds, nfds_t nfds, int timeout_ms)
{
	static struct fd_buf readfds = { NULL, 0 };
	static struct fd_buf writefds = { NULL, 0 };

	struct pollfd *pf;
	int res, fd_max = 0;
	struct timeval *tv = NULL;
	struct timeval tvreal;
	unsigned i;

	/* convert timeout_ms to timeval */
	if (timeout_ms >= 0)
	{
		tvreal.tv_sec = timeout_ms / 1000;
		tvreal.tv_usec = (timeout_ms % 1000) * 1000;
		tv = &tvreal;
	} else if (timeout_ms < -1)
		goto err_inval;

	/*
	 * Convert pollfds to fd sets.
	 */
	fdbuf_zero(&readfds);
	fdbuf_zero(&writefds);
	for (i = 0; i < nfds; i++)
	{
		pf = fds + i;
		if (pf->fd < 0)
			goto err_badf;

		/* sets must be equal size */
		if (!fdbuf_resize(&readfds, pf->fd))
			goto err_nomem;
		if (!fdbuf_resize(&writefds, pf->fd))
			goto err_nomem;

		if (pf->events & POLLIN)
			FD_SET((unsigned)pf->fd, readfds.set);
		if (pf->events & POLLOUT)
			FD_SET((unsigned)pf->fd, writefds.set);
		if (pf->fd > fd_max)
			fd_max = pf->fd;
	}

	res = select(fd_max + 1, readfds.set, writefds.set, NULL, tv);
	if (res <= 0)
		return res;

	/*
	 * select() and poll() count fd-s differently,
	 * need to recount them here.
	 */
	res = 0;

	for (i = 0; i < nfds; i++)
	{
		pf = fds + i;
		pf->revents = 0;
		if ((pf->events & POLLIN) && FD_ISSET(pf->fd, readfds.set))
			pf->revents |= POLLIN;
		if ((pf->events & POLLOUT) && FD_ISSET(pf->fd, writefds.set))
			pf->revents |= POLLOUT;
		if (pf->revents)
			res += 1;
	}
	return res;

err_nomem:
	errno = ENOMEM;
	return -1;

err_badf:
	errno = EBADF;
	return -1;
err_inval:
	errno = EINVAL;
	return -1;
}

#endif /* PLPROXY_POLL_COMPAT */

#ifndef HAVE_SIGACTION
#include <signal.h>
int sigaction(int sig, const struct sigaction *sa, struct sigaction *old)
{
	old->sa_handler = signal(sig, sa->sa_handler);
	if (old->sa_handler == SIG_ERR)
		return -1;
	return 0;
}
#endif

#ifdef WIN32
const char *win32_strerror(int e)
{
	static char buf[1024];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, e,
		      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		      buf, sizeof(buf), NULL);
	return buf;
}

void win32_eventlog(int level, const char *fmt, ...)
{
	static HANDLE evtHandle = INVALID_HANDLE_VALUE;
	int elevel;
	char buf[1024];
	const char *strlist[1] = { buf };
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	switch (level) {
	case LOG_CRIT:
	case LOG_ERR:
		elevel = EVENTLOG_ERROR_TYPE;
		break;
	case LOG_WARNING:
		elevel = EVENTLOG_WARNING_TYPE;
		break;
	default:
		elevel = EVENTLOG_INFORMATION_TYPE;
	}

	if (evtHandle == INVALID_HANDLE_VALUE) {
		evtHandle = RegisterEventSource(NULL, cf_syslog_ident);
		if (evtHandle == NULL || evtHandle == INVALID_HANDLE_VALUE) {
			evtHandle = INVALID_HANDLE_VALUE;
			return;
		}
	}
	ReportEvent(evtHandle, elevel, 0, 0, NULL, 1, 0, strlist, NULL);
}

/* create local TCP socket, idea from libevent/Tor */
int win32_socketpair(int d, int typ, int proto, int sv[2])
{
	int list = -1, s1 = -1, s2 = -1;
	struct sockaddr_in sa1, sa2;
	socklen_t slen = sizeof(sa1);
	int res;

	if (d != AF_INET && d != AF_UNIX)
		goto err_inval;
	if (proto || !sv)
		goto err_inval;

	/* prepare sockaddr for bind */
	memset(&sa1, 0, sizeof(sa1));
	sa1.sin_family = AF_INET;
	sa1.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa1.sin_port = htons(0);

	/* create listen socket */
	list = socket(AF_INET, typ, 0);
	if (list == -1)
		return -1;
	res = bind(list, (struct sockaddr *)&sa1, sizeof(sa1));
	if (res == -1)
		goto failed;
	res = listen(list, 1);
	if (res == -1)
		goto failed;

	/* read listen port */
	res = getsockname(list, (struct sockaddr *)&sa1, &slen);
	if (res == -1 || slen != sizeof(sa1))
		goto failed;

	/* connect to it */
	s1 = socket(AF_INET, typ, 0);
	if (s1 == -1)
		goto failed;
	res = connect(s1, (struct sockaddr *)&sa1, sizeof(sa1));
	if (res == -1)
		goto failed;

	/* and accept from other end */
	s2 = accept(list, (struct sockaddr *)&sa2, &slen);
	if (s2 == -1 || slen != sizeof(sa2))
		goto failed;

	/* sanity check */
	res = getsockname(s1, (struct sockaddr *)&sa1, &slen);
	if (res == -1 || slen != sizeof(sa1))
		goto failed;
	if (sa1.sin_port != sa2.sin_port)
		goto failed;

	closesocket(list);
	sv[0] = s1;
	sv[1] = s2;
	return 0;

failed:
	errno = (res == -1) ? WSAGetLastError() : EFAULT;
	if (list != -1) closesocket(list);
	if (s1 != -1) closesocket(s1);
	if (s2 != -1) closesocket(s2);
	return -1;

err_inval:
	errno = EINVAL;
	return -1;
}

#endif

