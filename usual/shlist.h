/*
 * Circular list for shared mem.
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

/**
 * @file
 *
 * Circular list for shared mem.
 *
 * Instead of pointers, it uses offsets from list head.
 */
#ifndef _USUAL_SHLIST_H_
#define _USUAL_SHLIST_H_

#include <usual/base.h>

/** List node/head.  Uses offsets from head instead of direct pointers. */
struct SHList {
	/** Offset to next elem */
	uintptr_t next;
	/** Offset from next elem */
	uintptr_t prev;
};

/*
 * Calculate offset relative to base.
 *
 * Instead of using some third pointer (eg. shmem start) as base,
 * we use list itself as base.  This results in simpler APi
 * and also means that empty list appears as zero-filled.
 */

static inline uintptr_t _ptr2sh(const void *base, const void *ptr)
{
	return (uintptr_t)((char *)ptr - (char *)base);
}

static inline void *_sh2ptr(const void *base, uintptr_t sh)
{
	return (void *)((char *)base + sh);
}

/*
 * List operations.
 */

/** Initialize list head */
static inline void shlist_init(struct SHList *list)
{
	list->next = _ptr2sh(list, list);
	list->prev = _ptr2sh(list, list);
}

/** Insert as last element */
static inline void shlist_append(struct SHList *list, struct SHList *item)
{
	struct SHList *last = _sh2ptr(list, list->prev);
	item->next = _ptr2sh(list, list);
	item->prev = _ptr2sh(list, last);
	list->prev = _ptr2sh(list, item);
	last->next = _ptr2sh(list, item);
}

/** Insert as first element */
static inline void shlist_prepend(struct SHList *list, struct SHList *item)
{
	struct SHList *first = _sh2ptr(list, list->next);
	item->next = _ptr2sh(list, first);
	item->prev = _ptr2sh(list, list);
	list->next = _ptr2sh(list, item);
	first->prev = _ptr2sh(list, item);
}

/** Remove an item */
static inline void shlist_remove(struct SHList *list, struct SHList *item)
{
	struct SHList *next = _sh2ptr(list, item->next);
	struct SHList *prev = _sh2ptr(list, item->prev);
	prev->next = item->next;
	next->prev = item->prev;
	item->next = item->prev = 0; /*  _ptr2sh(list, item) does not make sense here; */
}

/** No elements? */
static inline bool shlist_empty(const struct SHList *list)
{
	return list->next == list->prev;
}

static inline struct SHList *shlist_next(const struct SHList *list, const struct SHList *elem)
{
	return _sh2ptr(list, elem->next);
}

static inline struct SHList *shlist_prev(const struct SHList *list, const struct SHList *elem)
{
	return _sh2ptr(list, elem->prev);
}

/** Return first elem */
static inline struct SHList *shlist_first(const struct SHList *list)
{
	if (shlist_empty(list))
		return NULL;
	return _sh2ptr(list, list->next);
}

/** Return last elem */
static inline struct SHList *shlist_last(const struct SHList *list)
{
	if (shlist_empty(list))
		return NULL;
	return _sh2ptr(list, list->prev);
}

/** Remove first elem */
static inline struct SHList *shlist_pop(struct SHList *list)
{
	struct SHList *item = shlist_first(list);
	if (item)
		shlist_remove(list, item);
	return item;
}

/** Remove and return specific type of elem */
#define shlist_pop_type(list, type, field) ( \
	shlist_empty(list) ? NULL : container_of(shlist_pop(list), type, field))

/** Loop over list */
#define shlist_for_each(item, list) \
	for ((item) = _sh2ptr((list), (list)->next); \
	     (item) != (list); \
	     (item) = _sh2ptr((list), (item)->next))

/** Loop over list and allow removing item */
#define shlist_for_each_safe(item, list, tmp) \
	for ((item) = _sh2ptr((list), (list)->next), \
	      (tmp) = _sh2ptr((list), (item)->next); \
	     (item) != (list); \
	     (item) = (tmp), (tmp) = _sh2ptr((list), (tmp)->next))


#endif

