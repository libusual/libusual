/*
 * Wrapper for list.h that keeps track of number of items.
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

#ifndef _USUAL_STATLIST_H_
#define _USUAL_STATLIST_H_

#include <usual/list.h>

struct StatList {
	struct List head;
	int cur_count;
#ifdef LIST_DEBUG
	const char *name;
#endif
};

#ifdef LIST_DEBUG
#define STATLIST(var) struct StatList var = { {&var.head, &var.head}, 0, #var }
#else
#define STATLIST(var) struct StatList var = { {&var.head, &var.head}, 0 }
#endif

static inline void statlist_prepend(struct StatList *list, struct List *item)
{
	list_prepend(&list->head, item);
	list->cur_count++;
}

static inline void statlist_append(struct StatList *list, struct List *item)
{
	list_append(&list->head, item);
	list->cur_count++;
}

static inline void statlist_remove(struct StatList *list, struct List *item)
{
	list_del(item);
	list->cur_count--;

	//Assert(list->cur_count >= 0);
}

static inline void statlist_init(struct StatList *list, const char *name)
{
	list_init(&list->head);
	list->cur_count = 0;
#ifdef LIST_DEBUG
	list->name = name;
#endif
}

static inline int statlist_count(const struct StatList *list)
{
	//Assert(list->cur_count > 0 || list_empty(&list->head));
	return list->cur_count;
}

static inline struct List *statlist_pop(struct StatList *list)
{
	struct List *item = list_pop(&list->head);

	if (item)
		list->cur_count--;

	//Assert(list->cur_count >= 0);

	return item;
}

static inline struct List *statlist_first(const struct StatList *list)
{
	return list_first(&list->head);
}

static inline bool statlist_empty(const struct StatList *list)
{
	return list_empty(&list->head);
}

#define statlist_for_each(item, list) list_for_each(item, &((list)->head))
#define statlist_for_each_safe(item, list, tmp) list_for_each_safe(item, &((list)->head), tmp)

static inline void statlist_put_before(struct StatList *list, struct List *item, struct List *pos)
{
	list_append(pos, item);
	list->cur_count++;
}

static inline void statlist_put_after(struct StatList *list, struct List *item, struct List *pos)
{
	list_prepend(pos, item);
	list->cur_count++;
}

#endif /* __LIST_H_ */

