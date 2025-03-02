#include <usual/caslock.h>
#include <usual/logging.h>


void cas_lock_init(CasLock *lock) {
#ifdef WIN32
    InterlockedExchange(&lock->lock, 0);
#else
    lock->lock = 0;
#endif
    lock->owner = 0;
    lock->initialized = 1;
}

void cas_lock_acquire(CasLock *lock) {
    if (lock->initialized != 1) 
        fatal("Attempt to acquire an uninitialized lock!");

#ifdef WIN32
    while (InterlockedCompareExchange(&lock->lock, 1, 0) != 0) {
        SwitchToThread();
    }
#else
    while (!__sync_bool_compare_and_swap(&lock->lock, 0, 1)) {
        sched_yield();
    }
#endif
    lock->owner = GET_THREAD_ID();
}

void cas_lock_release(CasLock *lock) {
    if (lock->initialized != 1) 
        fatal("Attempt to acquire an uninitialized lock!");

#ifdef WIN32
    if (lock->owner != GET_THREAD_ID()) {
        fatal("Thread %lu tried to release a lock it does not own!", (unsigned long)GET_THREAD_ID());
    }
#else
    if (!pthread_equal(lock->owner, GET_THREAD_ID())) {
        fatal("Thread %lu tried to release a lock it does not own!", (unsigned long)GET_THREAD_ID());
    }
#endif

    lock->owner = 0;

#ifdef WIN32
    InterlockedExchange(&lock->lock, 0);
#else
    __sync_bool_compare_and_swap(&lock->lock, 1, 0);
#endif
}

void cas_lock_destroy(CasLock *lock) {
    // No cleanup required
}
