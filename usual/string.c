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
#include <usual/ctype.h>

#include <errno.h>

/*
 * Dynamic list of strings.
 */

struct StrList {
	struct StatList list;
	CxMem *ca;
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
		nstr = cx_strdup(slist->ca, str);
		if (!nstr)
			return false;
	}
	ok = strlist_append_ref(slist, nstr);
	if (!ok)
		cx_free(slist->ca, nstr);
	return ok;
}

bool strlist_append_ref(struct StrList *slist, const char *str)
{
	struct StrItem *item = cx_alloc(slist->ca, sizeof(*item));
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
	cx_free(slist->ca, item);
	return str;
}

struct StrList *strlist_new(CxMem *ca)
{
	struct StrList *slist = cx_alloc0(ca, sizeof(*slist));
	if (!slist)
		return NULL;
	statlist_init(&slist->list, "strlist");
	slist->ca = ca;
	return slist;
}

void strlist_free(struct StrList *slist)
{
	const char *s;
	if (!slist)
		return;
	while (!strlist_empty(slist)) {
		s = strlist_pop(slist);
		if (s)
			cx_free(slist->ca, s);
	}
	cx_free(slist->ca, slist);
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

#ifndef HAVE_MEMRCHR
void *memrchr(const void *s, int c, size_t n)
{
	const uint8_t *p = s;
	while (n--) {
		if (p[n] == c)
			return (void *)(p + n);
	}
	return NULL;
}
#endif

#ifndef HAVE_BASENAME
const char *basename(const char *path)
{
	const char *p, *p2;
	static char buf[256];
	unsigned len;

	if (path == NULL || path[0] == 0)
		return memcpy(buf, ".", 2);
	if ((p = strrchr(path, '/')) == NULL)
		return path;
	if (p[1])
		return p + 1;

	/* last char is '/' */
	for (p2 = p; p2 > path; p2--) {
		if (p2[-1] != '/') {
			len = p2 - path;
			if (len > sizeof(buf) - 1)
				len = sizeof(buf) - 1;
			memcpy(buf, p2 - len, len);
			buf[len] = 0;
			return basename(buf);
		}
	}
	/* path contains only '/' chars */
	return p;
}
#endif

#ifndef HAVE_DIRNAME
const char *dirname(const char *path)
{
	const char *p;
	size_t len;
	static char buf[1024];

	if (path == NULL || path[0] == 0)
		return memcpy(buf, ".", 2);

	/* ignore tailing '/' */
	len = strlen(path);
	while (len && path[len - 1] == '/')
		len--;
	if (!len)
		return memcpy(buf, "/", 2);

	/* find end of dirname, strip '/' */
	if ((p = memrchr(path, '/', len)) == NULL)
		return memcpy(buf, ".", 2);
	len = p - path;
	while (len && path[len - 1] == '/')
		len--;
	if (!len)
		return memcpy(buf, "/", 2);

	/* return it */
	if (len > sizeof(buf) - 1) {
		errno = ENAMETOOLONG;
		return NULL;
	}
	memcpy(buf, path, len);
	buf[len] = 0;
	return buf;
}
#endif

#ifdef WIN32
const char *win32_strerror(int e)
{
	static char buf[1024];
	return strerror_r(e, buf, sizeof(buf));
}
#endif

/* restore original strerror_r() */
#undef strerror_r

const char *usual_strerror_r(int e, char *dst, size_t dstlen)
{
#ifdef WIN32
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, e,
		      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		      dst, dstlen, NULL);
#else /* !WIN32 */

#ifdef STRERROR_R_CHAR_P
	dst = strerror_r(e, dst, dstlen);
#else
	if (strerror_r(e, dst, dstlen) != 0)
		strlcpy(dst, "ERR", dstlen);
#endif

#endif /* !WIN32 */

	return dst;
}


