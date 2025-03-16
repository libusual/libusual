/*
 * Thread-safe slab allocator wrapper.
 *
 * Based on the original slab allocator by Marko Kreen, adapted for multi-threaded use.
 */

#ifndef _USUAL_THREAD_SAFE_SLAB_H_
#define _USUAL_THREAD_SAFE_SLAB_H_

#include <usual/slab.h>


struct ThreadSafeSlab;


struct ThreadSafeSlab *thread_safe_slab_create(const char *name, unsigned obj_size, unsigned align,
                                               slab_init_fn init_func, CxMem *cx);
void thread_safe_slab_destroy(struct ThreadSafeSlab *ts_slab);
void *thread_safe_slab_alloc(struct ThreadSafeSlab *ts_slab) _MALLOC _MUSTCHECK;
void thread_safe_slab_free(struct ThreadSafeSlab *ts_slab, void *obj);
int thread_safe_slab_total_count(struct ThreadSafeSlab *ts_slab);
int thread_safe_slab_free_count(struct ThreadSafeSlab *ts_slab);
int thread_safe_slab_active_count(struct ThreadSafeSlab *ts_slab);
void thread_safe_slab_stats(slab_stat_fn cb_func, void *cb_arg);

#endif /* _USUAL_THREAD_SAFE_SLAB_H_ */
