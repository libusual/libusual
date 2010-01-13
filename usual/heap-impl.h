/*
 * Binary Heap.
 *
 * Copyright (c) 2009  Marko Kreen, Skype Technologies OÜ
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

/** @file
 * Binary heap.
 *
 * Summary - binary heap is sort of binary tree held inside array,
 * with following 2 properties:
 * - heap property: each node is "better" than it's childs.
 * - shape property: binary tree is complete, meaning all levels
 *   except the last one are fully filled.
 *
 * Instead of "min"- or "max"-heap, this is "best"-heap,
 * as it operates with user-defined heap_is_better() functions,
 * which is used to bubble elements on top.  Main reason
 * for such design is to make the comparisions inline.
 */

/*
 * If user wants to delete elements from the middle of heap,
 * this macro should be used to keep track where the element
 * is located.
 */
#ifndef SAVE_POS
#define SAVE_POS(ptr, pos)
#endif

#include <usual/base.h>

struct Heap {
	void **data;
	unsigned allocated;
	unsigned used;
};

/*
 * For user to be defined.
 *
 * Should return true if a needs to reach top before b,
 * false if not or equal.
 */
static inline bool heap_is_better(const void *a, const void *b);


/*
 * Low-level operations.
 */

static inline unsigned _heap_get_parent(unsigned i)
{
	return (i - 1) / 2;
}

static inline unsigned _heap_get_child(unsigned i, unsigned child_nr)
{
	return 2*i + 1 + child_nr;
}

static inline bool _heap_is_better(struct Heap *h, unsigned i1, unsigned i2)
{
	return heap_is_better(h->data[i1], h->data[i2]);
}

static inline void _heap_set(struct Heap *h, unsigned i, void *ptr)
{
	h->data[i] = ptr;
	SAVE_POS(ptr, i);
}

static inline void _heap_swap(struct Heap *h, unsigned i1, unsigned i2)
{
	void *tmp = h->data[i1];
	_heap_set(h, i1, h->data[i2]);
	_heap_set(h, i2, tmp);
}

static void _heap_bubble_up(struct Heap *h, unsigned i)
{
	unsigned p;
	while (i > 0) {
		p = _heap_get_parent(i);
		if (!_heap_is_better(h, i, p))
			break;
		_heap_swap(h, i, p);
		i = p;
	}
}

static void _heap_bubble_down(struct Heap *h, unsigned i)
{
	unsigned c = _heap_get_child(i, 0);
	while (c < h->used) {
		if (c + 1 < h->used) {
			if (_heap_is_better(h, c + 1, c))
				c = c + 1;
		}
		if (!_heap_is_better(h, c, i))
			break;
		_heap_swap(h, i, c);
		i = c;
		c = _heap_get_child(i, 0);
	}
}

static bool _heap_make_room(struct Heap *h, unsigned extra)
{
	void *tmp;
	unsigned newalloc;

	if (h->used + extra < h->allocated)
		return true;

	newalloc = h->allocated * 2;
	if (newalloc < 32)
		newalloc = 32;
	if (newalloc < h->used + extra)
		newalloc = h->used + extra;

	tmp = realloc(h->data, newalloc * sizeof(void *));
	if (!tmp)
		return false;
	h->data = tmp;
	h->allocated = newalloc;
	return true;
}


/*
 * Actual API.
 */


static void heap_init(struct Heap *h)
{
	h->data = NULL;
	h->allocated = 0;
	h->used = 0;
}

static void heap_destroy(struct Heap *h)
{
	free(h->data);
	heap_init(h);
}

static inline void *heap_get_top(struct Heap *h)
{
	return (h->used > 0) ? h->data[0] : NULL;
}

static inline bool heap_reserve(struct Heap *h, unsigned extra)
{
	if (h->used + extra < h->allocated)
		return true;

	return _heap_make_room(h, extra);
}

static bool heap_insert(struct Heap *h, void *ptr)
{
	unsigned i;

	if (!heap_reserve(h, 1))
		return false;

	i = h->used++;
	_heap_set(h, i, ptr);
	_heap_bubble_up(h, i);
	return true;
}

static void heap_delete_pos(struct Heap *h, unsigned pos)
{
	unsigned last;

	if (pos >= h->used)
		return;

	last = --h->used;
	if (pos == last) {
		h->data[last] = NULL;
		return;
	}

	_heap_set(h, pos, h->data[last]);
	h->data[last] = NULL;

	if (pos > 0 && _heap_is_better(h, pos, _heap_get_parent(pos)))
		_heap_bubble_up(h, pos);
	else
		_heap_bubble_down(h, pos);
}

static void heap_delete_top(struct Heap *h)
{
	heap_delete_pos(h, 0);
}

/* example and avoid 'unused' warnings */
static inline void _heap_example(void *el)
{
	struct Heap h;
	void *top;
	heap_init(&h);
	heap_insert(&h, el);
	top = heap_get_top(&h);
	heap_delete_top(&h);
	heap_destroy(&h);
}

