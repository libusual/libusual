/*
 * Crit-bit tree / binary radix tree.
 *
 * Copyright (c) 2009 Marko Kreen
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

#ifndef _USUAL_CBTREE_H_
#define _USUAL_CBTREE_H_

#include <usual/base.h>

/* returns length of the key */
typedef unsigned int	(*cbtree_getkey_func)(void *obj, const void **dst_p);
/* custom alloc */
typedef void *		(*cbtree_alloc_func)(void *arg, unsigned len);
typedef void		(*cbtree_free_func)(void *arg, void *ptr);
/* walk */
typedef bool		(*cbtree_walker_func)(void *arg, void *obj);

struct CBTree;

struct CBTree *cbtree_create(cbtree_getkey_func get_key_fn);
struct CBTree *cbtree_create_custom(cbtree_getkey_func get_key_fn,
				    void *arg,
				    cbtree_alloc_func f_alloc,
				    cbtree_free_func f_free);
void cbtree_destroy(struct CBTree *tree);

bool cbtree_insert(struct CBTree *tree, void *obj) _MUSTCHECK;
bool cbtree_delete(struct CBTree *tree, const void *key, unsigned klen);

void *cbtree_lookup(struct CBTree *tree, const void *key, unsigned klen);

bool cbtree_walk(struct CBTree *tree, cbtree_walker_func cb_func, void *cb_arg);

#endif

