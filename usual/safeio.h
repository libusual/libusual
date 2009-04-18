/*
 * libusual - Utility library for C
 *
 * Copyright (c) 2007-2009 Marko Kreen, Skype Technologies OÜ
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

#ifndef _USUAL_SAFEIO_H_
#define _USUAL_SAFEIO_H_

#include <usual/compat.h>


#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

int safe_read(int fd, void *buf, int len)                       _MUSTCHECK;
int safe_write(int fd, const void *buf, int len)                _MUSTCHECK;
int safe_recv(int fd, void *buf, int len, int flags)            _MUSTCHECK;
int safe_send(int fd, const void *buf, int len, int flags)      _MUSTCHECK;
int safe_close(int fd);
int safe_recvmsg(int fd, struct msghdr *msg, int flags)         _MUSTCHECK;
int safe_sendmsg(int fd, const struct msghdr *msg, int flags)   _MUSTCHECK;
int safe_connect(int fd, const struct sockaddr *sa, socklen_t sa_len)   _MUSTCHECK;
int safe_accept(int fd, struct sockaddr *sa, socklen_t *sa_len) _MUSTCHECK;

#endif
