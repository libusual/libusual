/** @file
 * Basic C environment.
 */

/*
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

#ifdef USUAL_TEST_CONFIG
#include "test_config.h"
#else
#include <usual/config.h>
#endif

/* solaris is broken otherwise */
#if defined(__sun)
#define _XPG4_2
#define __EXTENSIONS__
#endif

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
#include <assert.h>

#ifdef WIN32
#include <usual/base_win32.h>
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLEXPORT
#define DLLIMPORT
#endif

/** give offset of a field inside struct */
#ifndef offsetof
#define offsetof(type, field) ((unsigned long)&(((type *)0)->field))
#endif

/** given pointer to field inside struct, return pointer to struct */
#ifndef container_of
#define container_of(ptr, type, field) ((type *)((char *)(ptr) - offsetof(type, field)))
#endif

/** get alignment requirement for a type */
#ifndef alignof
#define alignof(type) offsetof(struct { char c; type t; }, t)
#endif

/** power-of-2 alignment */
#ifndef CUSTOM_ALIGN
#define CUSTOM_ALIGN(x, a) (((uintptr_t)(x) + (uintptr_t)(a) - 1) & ~((uintptr_t)(a) - 1))
#endif

/** preferred alignment */
#ifndef ALIGN
#define ALIGN(x)  CUSTOM_ALIGN(x, sizeof(long))
#endif

/** number of elements in array */
#define ARRAY_NELEM(a)	(sizeof(a) / sizeof((a)[0]))

/* how to specify array with unknown length */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define FLEX_ARRAY
#elif defined(__GNUC__) && (__GNUC__ >= 3)
#define FLEX_ARRAY
#else
#define FLEX_ARRAY 1
#endif

/** Make string token from C expression */
#define STR(x) _STR_(x)
#define _STR_(x) #x

/** Make single C token from 2 separate tokens */
#define CONCAT(a, b)    _CONCAT_(a, b)
#define _CONCAT_(a, b)  a ## b

/** Make single C token from 3 separate tokens */
#define CONCAT3(a, b, c)     _CONCAT3_(a, b, c)
#define _CONCAT3_(a, b, c)  a ## b ## c

/** Make single C token from 4 separate tokens */
#define CONCAT4(a, b, c, d)    _CONCAT4_(a, b, c, d)
#define _CONCAT4_(a, b, c, d)  a ## b ## c ## d

/**
 * @name Compiler attributes.
 */

/* Compiler detection for internal usage.  */
#define _COMPILER_GNUC(maj,min) (defined(__GNUC__) && \
	  ((__GNUC__ > (maj)) || (__GNUC__ == (maj) && __GNUC_MINOR__ >= (min))))
#define _COMPILER_CLANG(maj,min) (defined(__clang__) && \
	   ((__clang_major__ > (maj)) || (__clang_major__ == (maj) && __clang_minor__ >= (min))))
#define _COMPILER_MSC(ver) (defined(_MSC_VER) && (_MSC_VER >= (ver)))
#define _COMPILER_ICC(ver) (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= (ver)))

/** Disable padding for structure */
#define _PACKED			__attribute__((packed))

/*
 * Make sure __func__ works.
 */
#ifndef HAVE_FUNCNAME__FUNC
#define __func__ __FUNCTION__
#endif

/*
 * make compiler do something useful
 */

#ifndef _MUSTCHECK
#if defined(__GNUC__) && (__GNUC__ >= 4)

/** Show warning if function result is not used */
#define _MUSTCHECK              __attribute__((warn_unused_result))
/** Show warning if used */
#define _DEPRECATED             __attribute__((deprecated))
/** Check printf-style format and arg sanity */
#define _PRINTF(fmtpos, argpos) __attribute__((format(printf, fmtpos, argpos)))
/** Function returns new pointer */
#define _MALLOC                 __attribute__((malloc))
/** Disable 'unused' warning for function/argument. */
#define _UNUSED                 __attribute__((unused))
/** Do not inline function. */
#define _NOINLINE               __attribute__((noinline))
/** Indicates that function never returns */
#define _NORETURN               __attribute__((noreturn))

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
#define _NORETURN
#define unlikely(x) x
#define likely(x) x

#endif
#endif

/* @} */


/**
 * Compile-time assert.
 *
 * Expression must be evaluatable at compile time.
 * If false, stop compilation with message.
 *
 * It can be used in either global or function scope.
 */
#ifndef static_assert
#if _COMPILER_GNUC(4,6) || _COMPILER_CLANG(3,0) || _COMPILER_MSC(1600)
/* Version for new compilers */
#define static_assert(expr, msg) _Static_assert(expr, msg)
#else
/* Version for old compilers */
#define static_assert(expr, msg) enum { CONCAT4(static_assert_failure_, __LINE__, _, __COUNTER__) = 1/(1 != (1 + (expr))) }
#endif
#endif /* !static_assert */


/** assert() that uses <usual/logging> module  */
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
/** Compat: make free() accept const pointer */
#define free(x) _const_free(x)

/** Zeroing malloc */
_MUSTCHECK
static inline void *zmalloc(size_t len)
{
	return calloc(1, len);
}

#ifndef HAVE_POSIX_MEMALIGN
#define posix_memalign(a,b,c) usual_memalign(a,b,c)
/** Compat: posix_memalign() */
int posix_memalign(void **ptr_p, size_t align, size_t len);
#endif

#endif

