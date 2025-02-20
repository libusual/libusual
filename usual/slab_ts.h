/*
 * Thread-safe slab allocator wrapper.
 *
 * Based on original slab allocator by Marko Kreen, adapted for multi-threaded use.
 */

#ifndef _USUAL_THREAD_SAFE_SLAB_H_
#define _USUAL_THREAD_SAFE_SLAB_H_

#include <usual/slab.h>
#include <usual/pthread.h>

/** Reference to thread-safe slab */
struct ThreadSafeSlab;

/** Create new thread-safe slab context for specific size */
struct ThreadSafeSlab *thread_safe_slab_create(const char *name, unsigned obj_size, unsigned align,
                                               slab_init_fn init_func, CxMem *cx);

/** Free whole thread-safe context */
void thread_safe_slab_destroy(struct ThreadSafeSlab *ts_slab);

/** Allocate single object from thread-safe slab cache */
void *thread_safe_slab_alloc(struct ThreadSafeSlab *ts_slab) _MALLOC _MUSTCHECK;

/** Release single object back to thread-safe slab */
void thread_safe_slab_free(struct ThreadSafeSlab *ts_slab, void *obj);

/** Return sum of free and used objects in thread-safe slab */
int thread_safe_slab_total_count(struct ThreadSafeSlab *ts_slab);

/** Return number of free objects in thread-safe slab cache */
int thread_safe_slab_free_count(struct ThreadSafeSlab *ts_slab);

/** Return number of used objects in thread-safe slab */
int thread_safe_slab_active_count(struct ThreadSafeSlab *ts_slab);

void thread_safe_slab_stats(slab_stat_fn cb_func, void *cb_arg);

#endif /* _USUAL_THREAD_SAFE_SLAB_H_ */
