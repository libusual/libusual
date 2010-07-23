
/*
 * Extra allocators
 */

#include <usual/cxextra.h>
#include <usual/list.h>

#include <string.h>

/*
 * Tools for allocators.
 */

static inline void *p_move(const void *p, int ofs)
{
	return (char *)p + ofs;
}


/*
 * sample exit-on-failure wrapper
 */

static void *nofail_alloc(void *next, size_t len)
{
	void *p = cx_alloc(next, len);
	if (!p)
		exit(1);
	return p;
}

static void *nofail_realloc(void *next, void *ptr, size_t len)
{
	void *p = cx_realloc(next, ptr, len);
	if (!p)
		exit(1);
	return p;
}

static void nofail_free(void *next, const void *ptr)
{
	cx_free(next, ptr);
}

static void nofail_destroy(void *next)
{
	cx_destroy(next);
}

const struct CxOps cx_nofail_ops = {
	.c_alloc = nofail_alloc,
	.c_realloc = nofail_realloc,
	.c_free = nofail_free,
	.c_destroy = nofail_destroy,
};

const struct CxMem cx_libc_nofail = {
	.ops = &cx_nofail_ops,
	.ctx = (void*)&cx_libc_allocator,
};

/*
 * Append-only pool.
 */

struct CxPoolSeg {
	struct CxPoolSeg *prev;
	unsigned size;
	unsigned used;
};

struct CxPool {
	struct CxMem this;
	const struct CxMem *parent;
	struct CxPoolSeg *last;
	void *last_ptr;
};
#define POOL_HDR  ALIGN(sizeof(struct CxPoolSeg))

static void *pool_alloc(void *ctx, size_t size)
{
	struct CxPool *pool = ctx;
	struct CxPoolSeg *seg = pool->last;
	void *ptr;
	unsigned nsize;

	size = ALIGN(size);
	if (seg && seg->used + size <= seg->size) {
		ptr = p_move(seg, POOL_HDR + seg->used);
		seg->used += size;
		pool->last_ptr = ptr;
		return ptr;
	} else {
		nsize = seg ? (2 * seg->size) : 512;
		while (nsize < size)
			nsize *= 2;
		seg = cx_alloc(pool->parent, POOL_HDR + nsize);
		if (seg == NULL)
			return NULL;
		seg->used = size;
		seg->size = nsize;
		seg->prev = pool->last;
		pool->last = seg;
		ptr = p_move(seg, POOL_HDR);
		pool->last_ptr = ptr;
		return ptr;
	}
}

/* free only last item */
static void pool_free(void *ctx, const void *ptr)
{
	struct CxPool *pool = ctx;
	struct CxPoolSeg *cur = pool->last;
	const char *cstart;

	if (pool->last_ptr != ptr)
		return;
	cstart = p_move(cur, POOL_HDR);
	cur->used = (char *)ptr - cstart;
	pool->last_ptr = NULL;
}

/* realloc only last item */
static void *pool_realloc(void *ctx, void *ptr, size_t len)
{
	struct CxPool *pool = ctx;
	struct CxPoolSeg *seg = pool->last;
	char *cstart, *cused, *p = ptr;
	size_t olen;

	if (pool->last_ptr != ptr)
		return NULL;

	cstart = p_move(seg, POOL_HDR);
	cused = cstart + seg->used;

	olen = cused - p;
	if (seg->used - olen + len <= seg->size) {
		seg->used = p + len - cstart;
		return p;
	} else {
		p = pool_alloc(ctx, len);
		if (!p)
			return NULL;
		memcpy(p, ptr, olen);
		return p;
	}
}

static void pool_destroy(void *ctx)
{
	struct CxPool *pool = ctx;
	struct CxPoolSeg *cur, *tmp;
	if (!pool)
		return;
	for (cur = pool->last; cur; ) {
		tmp = cur->prev;
		cx_free(pool->parent, cur);
		cur = tmp;
	}
	cx_free(pool->parent, pool);
}

static const struct CxOps pool_ops = {
	.c_alloc = pool_alloc,
	.c_realloc = pool_realloc,
	.c_free = pool_free,
	.c_destroy = pool_destroy,
};

/*
 * public functions
 */

CxMem *cx_new_pool(CxMem *parent)
{
	struct CxPool *head;

	head = cx_alloc(parent, sizeof(*head));
	if (!head)
		return NULL;
	head->parent = parent;
	head->this.ops = &pool_ops;
	head->this.ctx = head;
	head->last = NULL;
	return &head->this;
}

/*
 * tree alloc
 */

#define TREE_HDR (int)(sizeof(struct CxTreeItem))

struct CxTree {
	struct CxMem this;
	CxMem *real;
	struct List alloc_list;
	struct List subtree_node;
	struct List subtree_list;
};

/* header for each allocation */
struct CxTreeItem {
	struct List node;
};

static void *tree_alloc(void *ctx, size_t len)
{
	struct CxTree *tree = ctx;
	struct CxTreeItem *item;

	item = cx_alloc(tree->real, TREE_HDR + len);
	if (!item)
		return NULL;
	list_init(&item->node);
	list_append(&tree->alloc_list, &item->node);

	return p_move(item, TREE_HDR);
}

static void *tree_realloc(void *ctx, void *ptr, size_t len)
{
	struct CxTree *t = ctx;
	struct CxTreeItem *item, *item2;
	item = p_move(ptr, -TREE_HDR);

	list_del(&item->node);
	item2 = cx_realloc(t->real, item, TREE_HDR + len);
	if (item2) {
		list_append(&t->alloc_list, &item2->node);
		return p_move(item2, TREE_HDR);
	} else {
		list_append(&t->alloc_list, &item->node);
		return NULL;
	}
}

static void tree_free(void *ctx, const void *ptr)
{
	struct CxTree *t = ctx;
	struct CxTreeItem *item;

	item = p_move(ptr, -TREE_HDR);
	list_del(&item->node);
	cx_free(t->real, item);
}

static void tree_destroy(void *ctx)
{
	struct CxTree *tree = ctx, *sub;
	struct CxTreeItem *item;
	struct List *el, *tmp;

	/* unregister from parent */
	list_del(&tree->subtree_node);

	/* free elements */
	list_for_each_safe(el, &tree->alloc_list, tmp) {
		list_del(el);
		item = container_of(el, struct CxTreeItem, node);
		cx_free(tree->real, item);
	}

	/* free subtrees */
	list_for_each_safe(el, &tree->subtree_list, tmp) {
		sub = container_of(el, struct CxTree, subtree_node);
		tree_destroy(sub);
	}

	/* free base struct */
	cx_free(tree->real, tree);
}

static const struct CxOps tree_ops = {
	.c_alloc = tree_alloc,
	.c_realloc = tree_realloc,
	.c_free = tree_free,
	.c_destroy = tree_destroy,
};


CxMem *cx_new_tree(CxMem *cx)
{
	struct CxTree *t, *parent = NULL;
	CxMem *real = cx;

	/*
	 * Try to allocate from real allocator.  Otherwise allocations
	 * will have double headers.
	 */
	if (cx->ops == &tree_ops) {
		parent = cx->ctx;
		real = parent->real;
	}

	/* initialize */
	t = cx_alloc(real, sizeof(*t));
	if (!t)
		return NULL;
	t->real = real;
	t->this.ops = &tree_ops;
	t->this.ctx = t;
	list_init(&t->alloc_list);
	list_init(&t->subtree_node);
	list_init(&t->subtree_list);

	/* register at parent */
	if (parent)
		list_append(&parent->subtree_list, &t->subtree_node);

	return &t->this;
}

