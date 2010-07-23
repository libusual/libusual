
#ifndef _USUAL_CXEXTRA_H_
#define _USUAL_CXEXTRA_H_

#include <usual/cxalloc.h>

/* wraps another allocator, exits on allocation failure */
extern const struct CxOps cx_nofail_ops;
/* nofail for libc */
extern CxMem cx_libc_nofail;

/*
 * Creates allocator that pools all memory together,
 * without keeping track of single objects, to be
 * freed all together in one shot.
 *
 * realloc(), free() are partially supported for the last
 * objec only.
 */
CxMem *cx_new_pool(CxMem *parent);

/*
 * Creates allocator that remebers all allocations done
 * under it and allows all of it to be freed together.
 *
 * Supports hierarchical trees.
 */
CxMem *cx_new_tree(CxMem *parent);

#endif

