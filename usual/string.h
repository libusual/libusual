/*
 * Basic C strings.
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

/*
 * Minimal spec-conforming implementations of strlcpy(), strlcat().
 */

#ifndef HAVE_STRLCPY
#define strlcpy(a,b,c) usual_strlcpy(a,b,c)

static inline size_t strlcpy(char *dst, const char *src, size_t n)
{
	size_t len = strlen(src);
	if (len < n) {
		memcpy(dst, src, len + 1);
	} else if (n > 0) {
		memcpy(dst, src, n - 1);
		dst[n - 1] = 0;
	}
	return len;
}

#endif /* !HAVE_STRLCPY */

#ifndef HAVE_STRLCAT
#define strlcat(a,b,c) usual_strlcat(a,b,c)

static inline size_t strlcat(char *dst, const char *src, size_t n)
{
	size_t pos = 0;
	while (pos < n && dst[pos])
		pos++;
	return pos + strlcpy(dst + pos, src, n - pos);
}

#endif /* !HAVE_STRLCAT */

typedef bool (*str_cb)(void *arg, const char *s);

struct StrList;
struct StrList *strlist_new(void);
void strlist_free(struct StrList *slist);
bool strlist_empty(struct StrList *slist);
bool strlist_append(struct StrList *slist, const char *str);
bool strlist_foreach(struct StrList *slist, str_cb cb_func, void *cb_arg);
const char *strlist_pop(struct StrList *slist);

bool parse_word_list(const char *s, str_cb cb_func, void *cb_arg);


#endif

