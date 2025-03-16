#include <usual/slab_ts.h>
#include <usual/slab.h>
#include <usual/spinlock.h>

struct ThreadSafeSlab {
    struct Slab *slab;
    SpinLock lock;
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

    spin_lock_init(&ts_slab->lock);
    return ts_slab;
}

void thread_safe_slab_destroy(struct ThreadSafeSlab *ts_slab) {
    if (!ts_slab)
        return;
    spin_lock_acquire(&ts_slab->lock);
    slab_destroy(ts_slab->slab);
    spin_lock_release(&ts_slab->lock);
}

void *thread_safe_slab_alloc(struct ThreadSafeSlab *ts_slab) {
    void *obj;
    spin_lock_acquire(&ts_slab->lock);
    obj = slab_alloc(ts_slab->slab);
    spin_lock_release(&ts_slab->lock);
    return obj;
}

void thread_safe_slab_free(struct ThreadSafeSlab *ts_slab, void *obj) {
    spin_lock_acquire(&ts_slab->lock);
    slab_free(ts_slab->slab, obj);
    spin_lock_release(&ts_slab->lock);
}

int thread_safe_slab_total_count(struct ThreadSafeSlab *ts_slab) {
    int count;
    spin_lock_acquire(&ts_slab->lock);
    count = slab_total_count(ts_slab->slab);
    spin_lock_release(&ts_slab->lock);
    return count;
}

int thread_safe_slab_free_count(struct ThreadSafeSlab *ts_slab) {
    int count;
    spin_lock_acquire(&ts_slab->lock);
    count = slab_free_count(ts_slab->slab);
    spin_lock_release(&ts_slab->lock);
    return count;
}

int thread_safe_slab_active_count(struct ThreadSafeSlab *ts_slab) {
    int count;
    spin_lock_acquire(&ts_slab->lock);
    count = slab_active_count(ts_slab->slab);
    spin_lock_release(&ts_slab->lock);
    return count;
}

void thread_safe_slab_stats(slab_stat_fn cb_func, void *cb_arg) {
    slab_stats(cb_func, cb_arg);
}
