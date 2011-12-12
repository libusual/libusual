/*
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

/**
 * \file
 * Theme include for strings.
 */

#ifndef _USUAL_STRING_H_
#define _USUAL_STRING_H_

#include <usual/cxalloc.h>

#include <string.h>

/**
 * @name  List of strings.
 * @{
 */

/** Callback signature */
typedef bool (*str_cb)(void *arg, const char *s);

struct StrList;
/** Allocate new string list */
struct StrList *strlist_new(CxMem *ca);
/** Free string string */
void strlist_free(struct StrList *slist);
/** Check if empty */
bool strlist_empty(struct StrList *slist);
/** Append copy of string. */
bool strlist_append(struct StrList *slist, const char *str);
/** Append reference, strlist now owns it. */
bool strlist_append_ref(struct StrList *slist, const char *str);
/** Call function on each element */
bool strlist_foreach(const struct StrList *slist, str_cb cb_func, void *cb_arg);
/** Remove and return first element */
const char *strlist_pop(struct StrList *slist);
/* @} */

/** Parse comma-separated elements from string and launch callback for each of them. */
bool parse_word_list(const char *s, str_cb cb_func, void *cb_arg);

#ifndef HAVE_STRLCPY
#define strlcpy(a,b,c) usual_strlcpy(a,b,c)
/** Compat: Safely copy string to fixed-length buffer.  */
size_t strlcpy(char *dst, const char *src, size_t n);
#endif

#ifndef HAVE_STRLCAT
#define strlcat(a,b,c) usual_strlcat(a,b,c)
/** Compat: Safely append string to fixed-length buffer. */
size_t strlcat(char *dst, const char *src, size_t n);
#endif

#ifndef HAVE_MEMRCHR
#define memrchr(a,b,c) usual_memrchr(a,b,c)
/** Compat: find byte in reverse direction */
void *memrchr(const void *s, int c, size_t n);
#endif

#ifndef HAVE_BASENAME
#undef basename
#define basename(a) usual_basename(a)
/** Compat: Return pointer to last non-path element.
    Never modifies path, returns either pointer inside path or static buffer.  */
const char *basename(const char *path);
#endif

#ifndef HAVE_DIRNAME
#undef dirname
#define dirname(a) usual_dirname(a)
/** Compat: Return directory part of pathname.
    Never modifies path, returns either pointer inside path or static buffer.  */
const char *dirname(const char *path);
#endif

/*
 * strerror, strerror_r
 */

#ifdef WIN32
const char *win32_strerror(int e);
/** Compat: strerror() for win32 */
#define strerror(x) win32_strerror(x)
#endif

const char *usual_strerror_r(int e, char *dst, size_t dstlen);
/** Compat: Provide GNU-style API: const char *strerror_r(int e, char *dst, size_t dstlen)  */
#define strerror_r(a,b,c) usual_strerror_r(a,b,c)

#endif

