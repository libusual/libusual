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

#include <stdio.h>

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
	snprintf(dst, dstlen, "%04d-%02d-%02d %02d:%02d:%02d",
		 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		 tm->tm_hour, tm->tm_min, tm->tm_sec);
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

/*
 * win32 compat
 */

#ifdef WIN32

/* unix epoch (1970) in seconds from windows epoch (1601) */
#define UNIX_EPOCH 11644473600LL

/* 1 sec in 100 nsec units */
#define FT_SEC 10000000LL

static void ft2tv(FILETIME *src, struct timeval *dst, bool use_epoch)
{
	ULARGE_INTEGER tmp;
	tmp.LowPart = src->dwLowDateTime;
	tmp.HighPart = src->dwHighDateTime;
	dst->tv_sec = (tmp.QuadPart / FT_SEC) - (use_epoch ? UNIX_EPOCH : 0);
	dst->tv_usec = (tmp.QuadPart % FT_SEC) / 10;
}

#ifndef HAVE_GETTIMEOFDAY

int gettimeofday(struct timeval * tp, void * tzp)
{
	FILETIME file_time;
	SYSTEMTIME system_time;

	/* read UTC timestamp */
	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);

	/* convert to timeval */
	ft2tv(&file_time, tp, true);

	return 0;
}

#endif /* !HAVE_GETTIMEOFDAY */

#ifndef HAVE_LOCALTIME_R

struct tm *localtime_r(const time_t *tp, struct tm *dst)
{
	ULARGE_INTEGER utc;
	FILETIME ft_utc;
	SYSTEMTIME st_utc, st_local;

	/* convert time_t to FILETIME */
	utc.QuadPart = (*tp + UNIX_EPOCH) * FT_SEC;
	ft_utc.dwLowDateTime = utc.LowPart;
	ft_utc.dwHighDateTime = utc.HighPart;

	/* split to parts and get local time */
	if (!FileTimeToSystemTime(&ft_utc, &st_utc))
		return NULL;
	if (!SystemTimeToTzSpecificLocalTime(NULL, &st_utc, &st_local))
		return NULL;

	/* fill struct tm */
	dst->tm_sec = st_local.wSecond;
	dst->tm_min = st_local.wMinute;
	dst->tm_hour = st_local.wHour;
	dst->tm_mday = st_local.wDay;
	dst->tm_mon = st_local.wMonth - 1;
	dst->tm_year = st_local.wYear - 1900;
	dst->tm_wday = st_local.wDayOfWeek;
	dst->tm_yday = 0;
	dst->tm_isdst = -1;
	return dst;
}

#endif /* !HAVE_LOCALTIME_R */

#ifndef HAVE_GETRUSAGE

int getrusage(int who, struct rusage *dst)
{
	FILETIME tcreate, texit, tkern, tuser;
	if (who != RUSAGE_SELF) {
		errno = EINVAL;
		return -1;
	}
	if (!GetProcessTimes(GetCurrentProcess(), &tcreate, &texit, &tkern, &tuser))
		return -1;
	ft2tv(&tuser, &dst->ru_utime, false);
	ft2tv(&tkern, &dst->ru_stime, false);
	return 0;
}

#endif /* !HAVE_GETRUSAGE */

#endif /* WIN32 */
