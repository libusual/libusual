#ifndef _USUAL_COMPAT_H_
#define _USUAL_COMPAT_H_

#include <usual/base.h>

#ifdef WIN32
#include <usual/win32.h>
#endif

#if !defined(HAVE_GETLINE)
#define getline(a,b,c) compat_getline(a,b,c)
int getline(char **line_p, size_t *size_p, void *f);
#endif


#if !defined(HAVE_POLL)
#define POLLIN		(1 << 0)
#define POLLOUT		(1 << 1)
#define POLLHUP		(1 << 2)
#define POLLPRI		(1 << 3)
#define POLLNVAL	(1 << 4)
#define POLLERR		(1 << 5)
#define poll(a,b,c)	compat_poll(a,b,c)
struct pollfd {
	int fd;
	short events;
	short revents;
};
typedef unsigned long nfds_t;
int poll(struct pollfd *fds, nfds_t nfds, int timeout_ms);
#endif


#ifndef HAVE_INET_NTOP
#define inet_ntop(a,b,c,d) compat_inet_ntop(a,b,c,d)
const char *inet_ntop(int af, const void *src, char *dst, int cnt);
#endif


#ifndef HAVE_GETPEEREID
#define getpeereid(a,b,c) compat_getpeereid(a,b,c)
int getpeereid(int fd, uid_t *uid_p, gid_t *gid_p);
#endif


#ifndef HAVE_BASENAME
#define basename(a) compat_basename(a)
const char *basename(const char *path);
#endif


#ifndef HAVE_SIGACTION
#define SA_SIGINFO 1
#define SA_RESTART 2
typedef struct siginfo_t siginfo_t;
struct sigaction {
	union {
		void     (*sa_handler)(int);
		void     (*sa_sigaction)(int, siginfo_t *, void *);
	};
	int sa_flags;
	int sa_mask;
};
#define sigemptyset(s)
#define sigfillset(s)
#define sigaddset(s, sig)
#define sigdelset(s, sig)
#define sigaction(a,b,c) compat_sigaction(a,b,c)
int sigaction(int sig, const struct sigaction *sa, struct sigaction *old);
#endif

#ifdef WIN32
#define socketpair(a,b,c,d) win32_socketpair(a,b,c,d)
int win32_socketpair(int d, int typ, int proto, int sv[2]);
#endif

#endif

