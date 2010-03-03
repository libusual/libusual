/*
 * Theme include for strings.
 * 
 * Copyright (c) 2007-2009  Marko Kreen, Skype Technologies OÜ
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

#ifndef _USUAL_STRING_H_
#define _USUAL_STRING_H_

#include <usual/base.h>

#include <string.h>

#ifdef HAVE_LIBGEN_H
#include <libgen.h>
#endif

#ifndef HAVE_STRLCPY
#define strlcpy(a,b,c) usual_strlcpy(a,b,c)
size_t strlcpy(char *dst, const char *src, size_t n);
#endif

#ifndef HAVE_STRLCAT
#define strlcat(a,b,c) usual_strlcat(a,b,c)
size_t strlcat(char *dst, const char *src, size_t n);
#endif

#ifndef HAVE_MEMRCHR
#define memrchr(a,b,c) usual_memrchr(a,b,c)
void *memrchr(const void *s, int c, size_t n);
#endif

typedef bool (*str_cb)(void *arg, const char *s);

struct StrList;
struct StrList *strlist_new(void);
void strlist_free(struct StrList *slist);
bool strlist_empty(struct StrList *slist);
bool strlist_append(struct StrList *slist, const char *str);
bool strlist_append_ref(struct StrList *slist, const char *str);
bool strlist_foreach(const struct StrList *slist, str_cb cb_func, void *cb_arg);
const char *strlist_pop(struct StrList *slist);

bool parse_word_list(const char *s, str_cb cb_func, void *cb_arg);

/*
 * fls(int)
 * flsl(long)
 * flsll(long long)
 *
 *   find MSB bit set, 1-based ofs, 0 if arg == 0
 */

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define _FLS(sfx, type) \
	return (x == 0) ? 0 : ((8*sizeof(type)) - __builtin_clz ## sfx(x))
#else
#define _FLS(sfx, type) \
	unsigned int bit; \
	if (x == 0) return 0; \
	/* count from smallest bit, assuming small values */ \
	for (bit = 1; x > 1; bit++) x >>= 1; \
	return bit
#endif

#ifndef HAVE_FLS
static inline int fls(int x) { _FLS(, int); }
#endif
#ifndef HAVE_FLSL
static inline int flsl(long x) { _FLS(l, long); }
#endif
#ifndef HAVE_FLSLL
static inline int flsll(long long x) { _FLS(ll, long long); }
#endif
#undef _FLS


#ifndef HAVE_BASENAME
#define basename(a) usual_basename(a)
const char *basename(const char *path);
#endif

#ifndef HAVE_DIRNAME
#define dirname(a) usual_dirname(a)
const char *dirname(const char *path);
#endif

/*
 * strerror, strerror_r
 */

#ifdef WIN32
const char *win32_strerror(int e);
#define strerror(x) win32_strerror(x)
#endif

/* convert native strerror_r() to GNU signature */
const char *usual_strerror_r(int e, char *dst, size_t dstlen);
#define strerror_r(a,b,c) usual_strerror_r(a,b,c)

#endif

