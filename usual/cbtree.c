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

/*
 * Associates a C string with user pointer (called "obj").
 *
 * Requires it's own internal nodes, thus not embeddable
 * to user structs.
 */

#include <usual/cbtree.h>

#include <usual/string.h>

/*
 * - Childs are either other nodes or user pointers.
 *   User pointers have lowest bit set.
 *
 * - All nodes have both childs.
 *
 * - Keys are handled as having infinite length,
 *   zero-filled after actual end.
 */

struct Node {
	struct Node *child[2];
	unsigned bitpos;
};

struct CBTree {
	struct Node *root;
	cbtree_getkey_func get_key;

	cbtree_alloc_func cb_alloc;
	cbtree_free_func cb_free;
	void *alloc_arg;
};

#define SAME_KEY 0xFFFFFFFF

/*
 * Low-level operations.
 */

/* does ptr point to user object or slot */
static inline int is_node(void *ptr)
{
	return ((uintptr_t)(ptr) & 1) == 0;
}

/* flag pointer as pointing to user object */
static inline void *set_external(const void *obj)
{
	return (void*)((uintptr_t)(obj) | 1);
}

/* remove flag from user pointer */
static inline void *get_external(void *extval)
{
	return (void*)((uintptr_t)(extval) & (~1));
}

/* get specific bit from string */
static inline unsigned get_bit(unsigned bitpos, const unsigned char *key, unsigned klen)
{
	unsigned pos = bitpos / 8;
	unsigned bit = 7 - (bitpos % 8);
	return (pos < klen) && (key[pos] & (1 << bit));
}

/* use callback to get key for a stored object */
static inline unsigned get_key(struct CBTree *tree, void *obj, const void **key_p)
{
	return tree->get_key(obj, key_p);
}

/* check if object key matches argument */
static inline bool key_matches(struct CBTree *tree, void *obj, const void *key, unsigned klen)
{
	const void *o_key;
	unsigned o_klen;
	o_klen = get_key(tree, obj, &o_key);
	return (o_klen == klen) && (memcmp(key, o_key, klen) == 0);
}

/* Find first differing bit on 2 strings.  */
static unsigned find_crit_bit(const unsigned char *a, unsigned alen, const unsigned char *b, unsigned blen)
{
	unsigned i, c, pos, av, bv;
	unsigned minlen = (alen > blen) ? blen : alen;
	unsigned maxlen = (alen > blen) ? alen : blen;

	/* find differing byte in common data */
	for (i = 0; i < minlen; i++) {
		av = a[i];
		bv = b[i];
		if (av != bv)
			goto found;
	}

	/* find differing byte when one side is zero-filled */
	for (; i < maxlen; i++) {
		av = (i < alen) ? a[i] : 0;
		bv = (i < blen) ? b[i] : 0;
		if (av != bv)
			goto found;
	}
	return SAME_KEY;

found:
	/* calculate bits that differ */
	c = av ^ bv;

	/* find the first one */
	pos = 8 - fls(c);

	return i * 8 + pos;
}


/*
 * Lookup
 */

/* walk nodes until external pointer is found */
static void *raw_lookup(struct CBTree *tree, const void *key, unsigned klen)
{
	struct Node *node = tree->root;
	unsigned bit;
	while (is_node(node)) {
		bit = get_bit(node->bitpos, key, klen);
		node = node->child[bit];
	}
	return get_external(node);
}

/* actual lookup.  returns obj ptr or NULL of not found */
void *cbtree_lookup(struct CBTree *tree, const void *key, unsigned klen)
{
	void *obj;

	if (!tree->root)
		return NULL;

	/* find match based on bits we know about */
	obj = raw_lookup(tree, key, klen);

	/* need to check if the object actually matches */
	if (key_matches(tree, obj, key, klen))
		return obj;

	return NULL;
}


/*
 * Insertion.
 */

/* node allocation */
static struct Node *new_node(struct CBTree *tree)
{
	struct Node *node = tree->cb_alloc(tree->alloc_arg, sizeof(*node));
	memset(node, 0, sizeof(*node));
	return node;
}

/* insert into empty tree */
static bool insert_first(struct CBTree *tree, void *obj)
{
	tree->root = set_external(obj);
	return true;
}

/* insert into specific bit-position */
static bool insert_at(struct CBTree *tree, unsigned newbit, const void *key, unsigned klen, void *obj)
{
	/* location of current node/obj pointer under examination */
	struct Node **pos = &tree->root;
	struct Node *node;
	unsigned bit;

	while (is_node(*pos) && ((*pos)->bitpos < newbit)) {
		bit = get_bit((*pos)->bitpos, key, klen);
		pos = &(*pos)->child[bit];
	}

	bit = get_bit(newbit, key, klen);
	node = new_node(tree);
	if (!node)
		return false;
	node->bitpos = newbit;
	node->child[bit] = set_external(obj);
	node->child[bit ^ 1] = *pos;
	*pos = node;
	return true;
}

/* actual insert: returns true -> insert ok or key found, false -> malloc failure */
bool cbtree_insert(struct CBTree *tree, void *obj)
{
	const void *key, *old_key;
	unsigned newbit, klen, old_klen;
	void *old_obj;

	if (!tree->root)
		return insert_first(tree, obj);

	/* current key */
	klen = get_key(tree, obj, &key);

	/* nearest key in tree */
	old_obj = raw_lookup(tree, key, klen);
	old_klen = get_key(tree, old_obj, &old_key);

	/* first differing bit is the target position */
	newbit = find_crit_bit(key, klen, old_key, old_klen);
	if (newbit == SAME_KEY)
		return true;
	return insert_at(tree, newbit, key, klen, obj);
}


/*
 * Key deletion.
 */

/* true -> object was found and removed, false -> not found */
bool cbtree_delete(struct CBTree *tree, const void *key, unsigned klen)
{
	void *obj, *tmp;
	unsigned bit = 0;
	/* location of current node/obj pointer under examination */
	struct Node **pos = &tree->root;
	/* if 'pos' has user obj, prev_pos has internal node pointing to it */
	struct Node **prev_pos = NULL;

	if (!tree->root)
		return false;

	/* match bits we know about */
	while (is_node(*pos)) {
		bit = get_bit((*pos)->bitpos, key, klen);
		prev_pos = pos;
		pos = &(*pos)->child[bit];
	}

	/* does the key actually matches */
	obj = get_external(*pos);
	if (!key_matches(tree, obj, key, klen))
		return false;

	/* drop the internal node pointing to our key */
	if (prev_pos) {
		tmp = *prev_pos;
		*prev_pos = (*prev_pos)->child[bit ^ 1];
		if (tree->cb_free)
			tree->cb_free(tree->alloc_arg, tmp);
	} else {
		tree->root = NULL;
	}
	return true;
}

/*
 * Management.
 */

struct CBTree *cbtree_create_custom(cbtree_getkey_func get_key_fn,
				    void *arg,
				    cbtree_alloc_func f_alloc,
				    cbtree_free_func f_free)
{
	struct CBTree *tree = f_alloc(arg, sizeof(*tree));
	if (!tree)
		return NULL;
	tree->root = NULL;
	tree->get_key = get_key_fn;
	tree->alloc_arg = arg;
	tree->cb_alloc = f_alloc;
	tree->cb_free = f_free;
	return tree;
}

static void *std_alloc(void *arg, unsigned len)
{
	return malloc(len);
}

static void std_free(void *arg, void *ptr)
{
	free(ptr);
}

/* create takes user function to query object for it's key */
struct CBTree *cbtree_create(cbtree_getkey_func get_key_fn)
{
	return cbtree_create_custom(get_key_fn, NULL, std_alloc, std_free);
}

/* recursive freeing */
static void destroy_node(struct CBTree *tree, struct Node *node)
{
	if (is_node(node->child[0]))
		destroy_node(tree, node->child[0]);
	if (is_node(node->child[1]))
		destroy_node(tree, node->child[1]);
	tree->cb_free(tree->alloc_arg, node);
}

/* Free tree and all it's internal nodes. */
void cbtree_destroy(struct CBTree *tree)
{
	if (!tree->cb_free)
		return;
	if (tree->root && is_node(tree->root))
		destroy_node(tree, tree->root);
	tree->root = NULL;
	tree->cb_free(tree->alloc_arg, tree);
}

