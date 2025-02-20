/*
 * Thread-safe wrapper for slab allocator using a single mutex.
 *
 * Based on original slab allocator by Marko Kreen, adapted for multi-threaded use.
 */

#include <usual/slab_ts.h>
#include <usual/statlist.h>

#ifndef USUAL_FAKE_SLAB

struct ThreadSafeSlab {
    struct Slab *slab;
    pthread_mutex_t mutex;
};

struct ThreadSafeSlab *thread_safe_slab_create(const char *name, unsigned obj_size, unsigned align,
                                               slab_init_fn init_func, CxMem *cx) {
    struct ThreadSafeSlab *ts_slab;

    ts_slab = cx ? cx_alloc0(cx, sizeof(*ts_slab)) : calloc(1, sizeof(*ts_slab));
    if (!ts_slab)
        return NULL;

    ts_slab->slab = slab_create(name, obj_size, align, init_func, cx);
    if (!ts_slab->slab) {
        free(ts_slab);
        return NULL;
    }

    pthread_mutex_init(&ts_slab->mutex, NULL);
    return ts_slab;
}

void thread_safe_slab_destroy(struct ThreadSafeSlab *ts_slab) {
    if (!ts_slab)
        return;
    
    pthread_mutex_lock(&ts_slab->mutex);
    slab_destroy(ts_slab->slab);
    pthread_mutex_unlock(&ts_slab->mutex);
    pthread_mutex_destroy(&ts_slab->mutex);
}

void *thread_safe_slab_alloc(struct ThreadSafeSlab *ts_slab) {
    void *obj;
    pthread_mutex_lock(&ts_slab->mutex);
    obj = slab_alloc(ts_slab->slab);
    pthread_mutex_unlock(&ts_slab->mutex);
    return obj;
}

void thread_safe_slab_free(struct ThreadSafeSlab *ts_slab, void *obj) {
    pthread_mutex_lock(&ts_slab->mutex);
    slab_free(ts_slab->slab, obj);
    pthread_mutex_unlock(&ts_slab->mutex);
}

int thread_safe_slab_total_count(struct ThreadSafeSlab *ts_slab) {
    pthread_mutex_lock(&ts_slab->mutex);
    int count = slab_total_count(ts_slab->slab);
    pthread_mutex_unlock(&ts_slab->mutex);
    return count;
}

int thread_safe_slab_free_count(struct ThreadSafeSlab *ts_slab) {
    pthread_mutex_lock(&ts_slab->mutex);
    int count = slab_free_count(ts_slab->slab);
    pthread_mutex_unlock(&ts_slab->mutex);
    return count;
}

int thread_safe_slab_active_count(struct ThreadSafeSlab *ts_slab) {
    pthread_mutex_lock(&ts_slab->mutex);
    int count = slab_active_count(ts_slab->slab);
    pthread_mutex_unlock(&ts_slab->mutex);
    return count;
}

void thread_safe_slab_stats(slab_stat_fn cb_func, void *cb_arg) {
    slab_stats(cb_func, cb_arg);
}

#endif
