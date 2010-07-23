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

#include <usual/cxalloc.h>

/* returns length of the key */
typedef unsigned int	(*cbtree_getkey_func)(void *ctx, void *obj, const void **dst_p);
/* walk */
typedef bool		(*cbtree_walker_func)(void *ctx, void *obj);

struct CBTree;

struct CBTree *cbtree_create(cbtree_getkey_func obj_key_cb,
			     cbtree_walker_func obj_free_cb,
			     void *cb_ctx,
			     CxMem *cx);
void cbtree_destroy(struct CBTree *tree);

bool cbtree_insert(struct CBTree *tree, void *obj) _MUSTCHECK;
bool cbtree_delete(struct CBTree *tree, const void *key, unsigned klen);

void *cbtree_lookup(struct CBTree *tree, const void *key, unsigned klen);

bool cbtree_walk(struct CBTree *tree, cbtree_walker_func cb_func, void *cb_arg);

#endif

