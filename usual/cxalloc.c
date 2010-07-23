
/*
 * Context Allocator framework.
 *
 * The idea is that each data structure is given a context to allocate from,
 * and it can create subcontext for that.  It is slightly more work to
 * use than palloc (PostgreSQL) or talloc (Samba), but it avoids the need
 * to have big fully-featured framework, that does everything at once.
 *
 * Instead you have small task-specific allocators, and you can always fall
 * back to raw malloc if you want to valgrind the code.
 *
 * Potential variants:
 * - fully-featured pooled
 * - randomly failing
 * - logging
 * - locking
 * - guard signatures
 * - palloc / talloc like API
 */

#include <usual/cxalloc.h>
#include <usual/statlist.h>

#include <string.h>

/*
 * Utility routines for cx_* API.
 */

void *cx_alloc(CxMem *cx, size_t len)
{
	if (!len)
		return NULL;
	return cx->ops->c_alloc(cx->ctx, len);
}

void *cx_realloc(CxMem *cx, void *ptr, size_t len)
{
	if (!ptr)
		return cx_alloc(cx, len);
	if (!len) {
		cx_free(cx, ptr);
		return NULL;
	}
	return cx->ops->c_realloc(cx->ctx, ptr, len);
}

void cx_free(CxMem *cx, const void *ptr)
{
	if (ptr)
		cx->ops->c_free(cx->ctx, ptr);
}

void cx_destroy(CxMem *cx)
{
	if (!cx)
		return;
	if (!cx->ops->c_destroy)
		abort();
	cx->ops->c_destroy(cx->ctx);
}

void *cx_alloc0(CxMem *cx, size_t len)
{
	void *p = cx_alloc(cx, len);
	if (p)
		memset(p, 0, len);
	return p;
}

void *cx_memdup(CxMem *cx, const void *src, size_t len)
{
	void *p = cx_alloc(cx, len);
	if (p)
		memcpy(p, src, len);
	return p;
}

void *cx_strdup(CxMem *cx, const char *s)
{
	return cx_memdup(cx, s, strlen(s));
}

/*
 * Base allocator that uses libc routines.
 */

static void *libc_alloc(void *ctx, size_t len)
{
	return malloc(len);
}

static void *libc_realloc(void *ctx, void *ptr, size_t len)
{
	return realloc(ptr, len);
}

static void libc_free(void *ctx, const void *ptr)
{
	free(ptr);
}

static const struct CxOps libc_alloc_ops = {
	.c_alloc = libc_alloc,
	.c_realloc = libc_realloc,
	.c_free = libc_free,
};

const struct CxMem cx_libc_allocator = {
	.ops = &libc_alloc_ops,
	.ctx = NULL,
};


