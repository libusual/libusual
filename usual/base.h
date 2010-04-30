/*
 * Basic C environment.
 *
 * Copyright (c) 2007-2009 Marko Kreen
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

#ifndef _USUAL_BASE_H_
#define _USUAL_BASE_H_

#include <usual/config.h>

#include <sys/types.h>
#include <sys/param.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#ifdef WIN32
#include <usual/base_win32.h>
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLEXPORT
#define DLLIMPORT
#endif

/* give offset of a field inside struct */
#ifndef offsetof
#define offsetof(type, field) ((unsigned long)&(((type *)0)->field))
#endif

/* given pointer to field inside struct, return pointer to struct */
#ifndef container_of
#define container_of(ptr, type, field) ((type *)((char *)(ptr) - offsetof(type, field)))
#endif

/* power-of-2 alignment */
#ifndef CUSTOM_ALIGN
#define CUSTOM_ALIGN(x, a) (((unsigned long)(x) + (a) - 1) & ~((a) - 1))
#endif

/* preferred alignment */
#ifndef ALIGN
#define ALIGN(x)  CUSTOM_ALIGN(x, sizeof(long))
#endif

/* number of elements in array */
#define ARRAY_NELEM(a)	(sizeof(a) / sizeof((a)[0]))

#define _PACKED			__attribute__((packed))

/*
 * make compiler do something useful
 */

#ifndef _MUSTCHECK
#if defined(__GNUC__) && (__GNUC__ >= 4)

/* additional error checking */
#define _MUSTCHECK              __attribute__((warn_unused_result))
#define _DEPRECATED             __attribute__((deprecated))
#define _PRINTF(fmtpos, argpos) __attribute__((format(printf, fmtpos, argpos)))
#define _MALLOC                 __attribute__((malloc))
#define _UNUSED                 __attribute__((unused))
#define _NOINLINE               __attribute__((noinline))

/* compiler hints - those do not seem to work well */
#define unlikely(x) __builtin_expect(!!(x), 0)
#define likely(x) __builtin_expect(!!(x), 1)

#else /* non gcc */

#define _MUSTCHECK
#define _DEPRECATED
#define _PRINTF(x,y)
#define _MALLOC
#define _UNUSED
#define _NOINLINE
#define unlikely(x) x
#define likely(x) x

#endif
#endif

/* assert() that uses our logging */
#ifndef Assert
#ifdef CASSERT
void log_fatal(const char *file, int line, const char *func, bool show_perror, void *ctx, const char *s, ...) _PRINTF(6, 7);
#define Assert(e) \
	do { \
		if (unlikely(!(e))) { \
			log_fatal(__FILE__, __LINE__, __func__, false, NULL, \
				  "Assert(%s) failed", #e); \
			abort(); \
		} \
	} while (0)
#else
#define Assert(e)
#endif
#endif

/* Fix posix bug by accepting const pointer.  */
static inline void _const_free(const void *p)
{
	free((void *)p);
}
#define free(x) _const_free(x)

/* Zeroing malloc */
_MUSTCHECK
static inline void *zmalloc(size_t len)
{
	return calloc(1, len);
}

#ifndef HAVE_POSIX_MEMALIGN
#define posix_memalign(a,b,c) usual_memalign(a,b,c)
int posix_memalign(void **ptr_p, size_t align, size_t len);
#endif

/* cpp expr -> string */
#define _STR_(identifier) #identifier
#define STR(x) _STR_(x)

#endif

