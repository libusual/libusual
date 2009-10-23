/*
 * Random win32 compat.
 *
 * Copyright (c) 2009  Marko Kreen
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

#include <usual/string.h>

#include <usual/mbuf.h>
#include <usual/statlist.h>

#include <errno.h>
#include <ctype.h>

/*
 * Dynamic list of strings.
 */

struct StrList {
	struct StatList list;
};

struct StrItem {
	struct List node;
	const char *str;
};

bool strlist_empty(struct StrList *slist)
{
	return statlist_empty(&slist->list);
}

bool strlist_append(struct StrList *slist, const char *str)
{
	const char *nstr = NULL;
	bool ok;
	if (str) {
		nstr = strdup(str);
		if (!nstr)
			return false;
	}
	ok = strlist_append_ref(slist, nstr);
	if (!ok)
		free(nstr);
	return ok;
}

bool strlist_append_ref(struct StrList *slist, const char *str)
{
	struct StrItem *item = calloc(1, sizeof(*item));
	if (!item)
		return false;
	list_init(&item->node);
	item->str = str;
	statlist_append(&slist->list, &item->node);
	return true;
}

const char *strlist_pop(struct StrList *slist)
{
	struct StrItem *item;
	struct List *el;
	const char *str;

	el = statlist_pop(&slist->list);
	if (!el)
		return NULL;

	item = container_of(el, struct StrItem, node);
	str = item->str;
	free(item);
	return str;
}

struct StrList *strlist_new(void)
{
	struct StrList *slist = calloc(1, sizeof(*slist));
	if (!slist)
		return NULL;
	statlist_init(&slist->list, "strlist");
	return slist;
}

void strlist_free(struct StrList *slist)
{
	const char *s;
	if (!slist)
		return;
	while (1) {
		s = strlist_pop(slist);
		if (!s)
			break;
		free(s);
	}
	free(slist);
}

bool strlist_foreach(const struct StrList *slist, str_cb func, void *arg)
{
	struct List *el;
	struct StrItem *item;
	statlist_for_each(el, &slist->list) {
		item = container_of(el, struct StrItem, node);
		if (!func(arg, item->str))
			return false;
	}
	return true;
}

/*
 * Parse comma separated words.
 */

static inline const char *skip_ws(const char *p)
{
	while (*p && isspace(*p))
		p++;
	return p;
}


bool parse_word_list(const char *s, str_cb cb_func, void *cb_arg)
{
	struct MBuf buf;
	const char *p = s;
	const char *start, *end;

	mbuf_init_dynamic(&buf);
	while (*p) {
		/* parse word */
		p = skip_ws(p);
		start = p;
		while (*p && *p != ',')
			p++;
		end = p;
		while (end > start && isspace(*(end - 1)))
			end--;

		/* parse comma */
		if (*p) {
			if (*p == ',') {
				p++;
			} else {
				goto failed_syntax;
			}
		}

		/* extract string */
		if (start == end)
			goto failed_syntax;
		if (!mbuf_write(&buf, start, end - start))
			goto failed;
		if (!mbuf_write_byte(&buf, 0))
			goto failed;

		/* launch callback */
		if (!cb_func(cb_arg, (const char *)buf.data))
			goto failed;

		/* reset */
		mbuf_rewind_writer(&buf);
	}
	mbuf_free(&buf);
	return true;

failed_syntax:
	errno = EINVAL;
failed:
	mbuf_free(&buf);
	return false;
}

/*
 * Minimal spec-conforming implementations of strlcpy(), strlcat().
 */

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dst, const char *src, size_t n)
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
#endif

#ifndef HAVE_STRLCAT
size_t strlcat(char *dst, const char *src, size_t n)
{
	size_t pos = 0;
	while (pos < n && dst[pos])
		pos++;
	return pos + strlcpy(dst + pos, src, n - pos);
}
#endif

#ifndef HAVE_BASENAME
const char *basename(const char *path)
{
	const char *p;
	if (path == NULL || path[0] == 0)
		return ".";
	if ((p = strrchr(path, '/')) != NULL)
		return p[1] ? p + 1 : p;
	return path;
}
#endif

#ifdef WIN32
const char *win32_strerror(int e)
{
	static char buf[1024];
	return strerror_r(e, buf, sizeof(buf));
}
const char *win32_strerror_r(int e, char *dst, size_t dstlen)
{
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, e,
		      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		      dst, dstlen, NULL);
	return dst;
}
#else
const char *wrap_strerror_r(int e, char *dst, size_t dstlen)
{
#undef strerror_r
#ifdef STRERROR_R_CHAR_P
	return strerror_r(e, dst, dstlen);
#else
	if (strerror_r(e, dst, dstlen) != 0)
		strlcpy(dst, "ERR", dstlen);
	return dst;
#endif
}
#endif


