
#ifndef _USUAL_CXALLOC_H_
#define _USUAL_CXALLOC_H_

#include <usual/base.h>

/*
 * Ops for allocator that takes context.
 */
struct CxOps {
	void *(*c_alloc)(void *ctx, size_t len);
	void *(*c_realloc)(void *ctx, void *p, size_t len);
	void (*c_free)(void *ctx, const void *p);
	void (*c_destroy)(void *ctx);
};

/*
 * Specific memory allocation context.
 */
struct CxMem {
	const struct CxOps *ops;
	void *ctx;
};

typedef const struct CxMem CxMem;

/*
 * Basic operations on allocation context.
 */

void *cx_alloc(CxMem *cx, size_t len) _MALLOC;
void *cx_realloc(CxMem *cx, void *ptr, size_t len);
void cx_free(CxMem *cx, const void *ptr);
void cx_destroy(CxMem *cx);
void *cx_alloc0(CxMem *cx, size_t len) _MALLOC;
void *cx_memdup(CxMem *cx, const void *src, size_t len) _MALLOC;
void *cx_strdup(CxMem *cx, const char *str) _MALLOC;


/* Allocator that uses libc malloc/realloc/free */
extern CxMem cx_libc_allocator;

/* Default allocator */
#ifndef USUAL_ALLOC
#define USUAL_ALLOC (&cx_libc_allocator)
#endif

#endif

