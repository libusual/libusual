/*
 * Circular doubly linked list implementation.
 * 
 * Copyright (c) 2007 Marko Kreen, Skype Technologies OÜ
 * 
 * Permission to use, copy, modify, and distribute this software for any
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

#ifndef _USUAL_LIST_H_
#define _USUAL_LIST_H_

#include <usual/base.h>

/* list type */
struct List {
	struct List *next;
	struct List *prev;
};

#define LIST(var) struct List var = { &var, &var }

/* initialize struct */
static inline void list_init(struct List *list)
{
	list->next = list->prev = list;
}

/* is list empty? */
static inline int list_empty(const struct List *list)
{
	return list->next == list;
}

/* add item to the start of the list */
static inline struct List *list_prepend(struct List *list, struct List *item)
{
	item->next = list->next;
	item->prev = list;
	list->next->prev = item;
	list->next = item;
	return item;
}

/* add item to the end of the list */
static inline struct List *list_append(struct List *list, struct List *item)
{
	item->next = list;
	item->prev = list->prev;
	list->prev->next = item;
	list->prev = item;
	return item;
}

/* remove item from list */
static inline struct List *list_del(struct List *item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
	item->next = item->prev = item;
	return item;
}

/* remove first from list and return */
static inline struct List *list_pop(struct List *list)
{
	if (list_empty(list))
		return NULL;
	return list_del(list->next);
}

/* remove first from list and return */
static inline struct List *list_first(const struct List *list)
{
	if (list_empty(list))
		return NULL;
	return list->next;
}

/* remove first elem from list and return with casting */
#define list_pop_type(list, typ, field) \
	(list_empty(list) ? NULL \
	 : container_of(list_del((list)->next), typ, field))

/* loop over list */
#define list_for_each(item, list) \
	for ((item) = (list)->next; \
	     (item) != (list); \
	     (item) = (item)->next)

/* loop over list and allow removing item */
#define list_for_each_safe(item, list, tmp) \
	for ((item) = (list)->next, (tmp) = (list)->next->next; \
	     (item) != (list); \
	     (item) = (tmp), (tmp) = (tmp)->next)

#endif

