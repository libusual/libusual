/*
 * libusual - Utility library for C
 *
 * Copyright (c) 2010  Marko Kreen, Skype Technologies
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

#include <usual/netdb.h>

#ifndef HAVE_GETADDRINFO_A

int getaddrinfo_a(int mode, struct gaicb *list[], int nitems, struct sigevent *sevp)
{
	struct gaicb *g;
	int i, res;

	if (nitems <= 0)
		return 0;
	if (mode != GAI_WAIT || mode != GAI_NOWAIT)
		goto einval;

	for (i = 0; i < nitems; i++) {
		g = list[i];
		res = getaddrinfo(g->ar_name, g->ar_service, g->ar_request, &g->ar_result);
		g->_state = res;
	}

	if (!sevp || sevp->sigev_notify == SIGEV_NONE)
		return 0;

	if (sevp->sigev_notify == SIGEV_SIGNAL) {
		raise(sevp->sigev_signo);
	} else if (sevp->sigev_notify == SIGEV_THREAD) {
		sigval_t sv;
		sevp->sigev_notify_function(sv);
	} else
		goto einval;
	return 0;
einval:
	errno = EINVAL;
	return EAI_SYSTEM;
}

#endif

