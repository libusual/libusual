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
	const char *(*get_key)(void *obj);
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
static inline unsigned get_bit(unsigned bitpos, const char *key, unsigned klen)
{
	unsigned pos = bitpos / 8;
	unsigned bit = 7 - (bitpos % 8);
	return (pos < klen) && (key[pos] & (1 << bit));
}

/* use callback to get key for a stored object */
static inline const char *get_key(struct CBTree *tree, void *obj)
{
	return tree->get_key(obj);
}

/* Find first differing bit on 2 zero-terminated strings.  */
static unsigned find_crit_bit(const char *a, const char *b)
{
	unsigned i, c, pos;

	/* find differing byte */
	for (i = 0; ; i++) {
		/* this handles also size difference */
		if (a[i] != b[i])
			break;

		/* equal strings? */
		if (a[i] == 0)
			return SAME_KEY;
	}

	/* calculate bits that differ */
	c = a[i] ^ b[i];

	/* find the first one */
	pos = 8 - fls(c);

	return i * 8 + pos;
}


/*
 * Lookup
 */

/* walk nodes until external pointer is found */
static void *raw_lookup(struct CBTree *tree, const char *key, unsigned klen)
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
void *cbtree_lookup(struct CBTree *tree, const char *key)
{
	unsigned klen;
	void *obj;

	if (!tree->root)
		return NULL;

	/* find match based on bits we know about */
	klen = strlen(key);
	obj = raw_lookup(tree, key, klen);

	/* need to check if the object actually matches */
	if (strcmp(key, get_key(tree, obj)) == 0)
		return obj;

	return NULL;
}


/*
 * Insertion.
 */

/* node allocation */
static struct Node *new_node(void)
{
	struct Node *node = malloc(sizeof(*node));
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
static bool insert_at(struct CBTree *tree, unsigned newbit, const char *key, unsigned klen, void *obj)
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
	node = new_node();
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
	const char *key;
	unsigned newbit, klen;
	void *old_obj;

	if (!tree->root)
		return insert_first(tree, obj);

	/* match bits we know about */
	key = get_key(tree, obj);
	klen = strlen(key);
	old_obj = raw_lookup(tree, key, klen);

	/* first differing bit is the target position */
	newbit = find_crit_bit(key, get_key(tree, old_obj));
	if (newbit == SAME_KEY)
		return true;
	return insert_at(tree, newbit, key, klen, obj);
}


/*
 * Key deletion.
 */

/* true -> object was found and removed, false -> not found */
bool cbtree_delete(struct CBTree *tree, const char *key)
{
	void *obj, *tmp;
	unsigned bit = 0;
	unsigned klen = strlen(key);
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
	if (strcmp(key, get_key(tree, obj)) != 0)
		return false;

	/* drop the internal node pointing to our key */
	if (prev_pos) {
		tmp = *prev_pos;
		*prev_pos = (*prev_pos)->child[bit ^ 1];
		free(tmp);
	} else {
		tree->root = NULL;
	}
	return true;
}

/*
 * Management.
 */

/* create takes user function to query object for it's key */
struct CBTree *cbtree_create(cbtree_getkey_func get_key_fn)
{
	struct CBTree *tree = malloc(sizeof(*tree));
	tree->root = NULL;
	tree->get_key = get_key_fn;
	return tree;
}

/* recursive freeing */
static void destroy_node(struct Node *node)
{
	if (is_node(node->child[0]))
		destroy_node(node->child[0]);
	if (is_node(node->child[1]))
		destroy_node(node->child[1]);
	free(node);
}

/* Free tree and all it's internal nodes. */
void cbtree_destroy(struct CBTree *tree)
{
	if (tree->root && is_node(tree->root))
		destroy_node(tree->root);
	tree->root = NULL;
	free(tree);
}

