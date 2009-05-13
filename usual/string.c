#include <usual/string.h>

#include <usual/alloc.h>
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
	struct StrItem *item = calloc(1, sizeof(*item));
	if (!item)
		return false;
	list_init(&item->node);
	item->str = strdup(str);
	if (!item->str) {
		free(item);
		return false;
	}
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

bool strlist_foreach(struct StrList *slist, str_cb func, void *arg)
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

