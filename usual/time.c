/*
 * Common time functions.
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

#include <usual/time.h>

#include <sys/time.h>
#include <time.h>
#include <stdio.h>

#include <usual/compat.h>

char *format_time_ms(usec_t time, char *dst, unsigned dstlen)
{
	struct tm *tm, tmbuf;
	struct timeval tv;
	time_t sec;

	if (!time) {
		gettimeofday(&tv, NULL);
	} else {
		tv.tv_sec = time / USEC;
		tv.tv_usec = time % USEC;
	}

	sec = tv.tv_sec;
	tm = localtime_r(&sec, &tmbuf);
	snprintf(dst, dstlen, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		 tm->tm_hour, tm->tm_min, tm->tm_sec,
		 (int)(tv.tv_usec / 1000));
	return dst;
}

char *format_time_s(usec_t time, char *dst, unsigned dstlen)
{
	time_t s;
	struct tm tbuf, *tm;
	if (!time) {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		s = tv.tv_sec;
	} else {
		s = time / USEC;
	}
	tm = localtime_r(&s, &tbuf);
	strftime(dst, dstlen, "%Y-%m-%d %H:%M:%S", tm);
	return dst;
}


/* read current time */
usec_t get_time_usec(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (usec_t)tv.tv_sec * USEC + tv.tv_usec;
}

static usec_t _time_cache;

/* read cached time */
usec_t get_cached_time(void)
{
	if (!_time_cache)
		_time_cache = get_time_usec();
	return _time_cache;
}

/* forget cached time, let next read fill it */
void reset_time_cache(void)
{
	_time_cache = 0;
}

