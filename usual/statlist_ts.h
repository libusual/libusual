#ifndef _USUAL_THREAD_SAFE_STATLIST_H_
#define _USUAL_THREAD_SAFE_STATLIST_H_

#include <usual/statlist.h>
#include <usual/pthread.h>

/**
 * Header structure for ThreadSafeStatList.
 * This wraps StatList with a mutex for thread safety.
 */
struct ThreadSafeStatList {
    struct StatList list;
    pthread_mutex_t mutex;
};

/** Define and initialize ThreadSafeStatList head */
#ifdef LIST_DEBUG
#define THREAD_SAFE_STATLIST(var) struct ThreadSafeStatList var = { { {&var.list.head, &var.list.head}, 0, #var }, PTHREAD_MUTEX_INITIALIZER }
#else
#define THREAD_SAFE_STATLIST(var) struct ThreadSafeStatList var = { { {&var.list.head, &var.list.head}, 0 }, PTHREAD_MUTEX_INITIALIZER }
#endif

/** Initialize ThreadSafeStatList head */
static inline void thread_safe_statlist_init(struct ThreadSafeStatList *list, const char *name) {
    statlist_init(&list->list, name);
    pthread_mutex_init(&list->mutex, NULL);
}

/** Destroy the mutex */
static inline void thread_safe_statlist_destroy(struct ThreadSafeStatList *list) {
    pthread_mutex_destroy(&list->mutex);
}

/** Add to the start of the list */
static inline void thread_safe_statlist_prepend(struct ThreadSafeStatList *list, struct List *item) {
    pthread_mutex_lock(&list->mutex);
    statlist_prepend(&list->list, item);
    pthread_mutex_unlock(&list->mutex);
}

/** Add to the end of the list */
static inline void thread_safe_statlist_append(struct ThreadSafeStatList *list, struct List *item) {
    pthread_mutex_lock(&list->mutex);
    statlist_append(&list->list, item);
    pthread_mutex_unlock(&list->mutex);
}

/** Remove element from the list */
static inline void thread_safe_statlist_remove(struct ThreadSafeStatList *list, struct List *item) {
    pthread_mutex_lock(&list->mutex);
    statlist_remove(&list->list, item);
    pthread_mutex_unlock(&list->mutex);
}

/** Remove and return first element */
static inline struct List *thread_safe_statlist_pop(struct ThreadSafeStatList *list) {
    pthread_mutex_lock(&list->mutex);
    struct List *item = statlist_pop(&list->list);
    pthread_mutex_unlock(&list->mutex);
    return item;
}

/** Return first element */
static inline struct List *thread_safe_statlist_first(struct ThreadSafeStatList *list) {
    pthread_mutex_lock(&list->mutex);
    struct List *item = statlist_first(&list->list);
    pthread_mutex_unlock(&list->mutex);
    return item;
}

/** Return last element */
static inline struct List *thread_safe_statlist_last(struct ThreadSafeStatList *list) {
    pthread_mutex_lock(&list->mutex);
    struct List *item = statlist_last(&list->list);
    pthread_mutex_unlock(&list->mutex);
    return item;
}

/** Is list empty */
static inline bool thread_safe_statlist_empty(struct ThreadSafeStatList *list) {
    pthread_mutex_lock(&list->mutex);
    bool empty = statlist_empty(&list->list);
    pthread_mutex_unlock(&list->mutex);
    return empty;
}

/** Return number of elements currently in list */
static inline int thread_safe_statlist_count(struct ThreadSafeStatList *list) {
    pthread_mutex_lock(&list->mutex);
    int count = statlist_count(&list->list);
    pthread_mutex_unlock(&list->mutex);
    return count;
}

/** Put item before another */
static inline void thread_safe_statlist_put_before(struct ThreadSafeStatList *list, struct List *item, struct List *pos) {
    pthread_mutex_lock(&list->mutex);
    statlist_put_before(&list->list, item, pos);
    pthread_mutex_unlock(&list->mutex);
}

/** Put item after another */
static inline void thread_safe_statlist_put_after(struct ThreadSafeStatList *list, struct List *item, struct List *pos) {
    pthread_mutex_lock(&list->mutex);
    statlist_put_after(&list->list, item, pos);
    pthread_mutex_unlock(&list->mutex);
}

/** Loop over thread-safe list */
static inline void thread_safe_statlist_iterate(struct ThreadSafeStatList *list, void (*func)(struct List *)) {
    pthread_mutex_lock(&list->mutex);
    struct List *item;
    statlist_for_each(item, &list->list) {
        func(item);
    }
    pthread_mutex_unlock(&list->mutex);
}

/** Loop over thread-safe list backwards */
static inline void thread_safe_statlist_iterate_reverse(struct ThreadSafeStatList *list, void (*func)(struct List *)) {
    pthread_mutex_lock(&list->mutex);
    struct List *item;
    statlist_for_each_reverse(item, &list->list) {
        func(item);
    }
    pthread_mutex_unlock(&list->mutex);
}

#endif /* _USUAL_THREAD_SAFE_STATLIST_H_ */
