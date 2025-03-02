#include <usual/caslock.h>
#include <usual/logging.h>

#define CAS_LOCK_UNLOCKED 0
#define CAS_LOCK_LOCKED 1
#define CAS_LOCK_UNINITIALIZED 0
#define CAS_LOCK_INITIALIZED 1

void cas_lock_init(CasLock *lock) {
#ifdef WIN32
    InterlockedExchange(&lock->lock, CAS_LOCK_UNLOCKED);
#else
    lock->lock = CAS_LOCK_UNLOCKED;
#endif
    lock->owner = 0;
    lock->initialized = CAS_LOCK_INITIALIZED;
}

void cas_lock_acquire(CasLock *lock) {
    if (lock->initialized != CAS_LOCK_INITIALIZED) 
        fatal("Attempt to acquire an uninitialized lock!");

#ifdef WIN32
    while (InterlockedCompareExchange(&lock->lock, CAS_LOCK_LOCKED, CAS_LOCK_UNLOCKED) != 0) {
        SwitchToThread();
    }
#else
    while (!__sync_bool_compare_and_swap(&lock->lock, CAS_LOCK_UNLOCKED, CAS_LOCK_LOCKED)) {
        sched_yield();
    }
#endif
    lock->owner = GET_THREAD_ID();
}

void cas_lock_release(CasLock *lock) {
    if (lock->initialized != CAS_LOCK_INITIALIZED) 
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
    InterlockedExchange(&lock->lock, CAS_LOCK_UNLOCKED);
#else
    __sync_bool_compare_and_swap(&lock->lock, CAS_LOCK_LOCKED, CAS_LOCK_UNLOCKED);
#endif
}

void cas_lock_destroy(CasLock *lock) {
    // No cleanup required
}
