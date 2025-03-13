#include <usual/logging.h>
#include <usual/spinlock.h>

#define SPIN_LOCK_UNLOCKED 0
#define SPIN_LOCK_LOCKED 1
#define SPIN_LOCK_INITIALIZED 1

void spin_lock_init(SpinLock *lock) {
#ifdef WIN32
    InterlockedExchange(&lock->lock, SPIN_LOCK_UNLOCKED);
#else
    lock->lock = SPIN_LOCK_UNLOCKED;
#endif
    lock->owner = 0;
    lock->initialized = SPIN_LOCK_INITIALIZED;
}

void spin_lock_acquire(SpinLock *lock) {
    if (lock->initialized != SPIN_LOCK_INITIALIZED) 
        fatal("Attempt to acquire an uninitialized lock!");

#ifdef WIN32
    while (InterlockedCompareExchange(&lock->lock, SPIN_LOCK_LOCKED, SPIN_LOCK_UNLOCKED) != 0) {
        SwitchToThread();
    }
#else
    while (!__sync_bool_compare_and_swap(&lock->lock, SPIN_LOCK_UNLOCKED, SPIN_LOCK_LOCKED)) {
        sched_yield();
    }
#endif
    lock->owner = GET_THREAD_ID();
}

void spin_lock_release(SpinLock *lock) {
    if (lock->initialized != SPIN_LOCK_INITIALIZED) 
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
    InterlockedExchange(&lock->lock, SPIN_LOCK_UNLOCKED);
#else
    __sync_bool_compare_and_swap(&lock->lock, SPIN_LOCK_LOCKED, SPIN_LOCK_UNLOCKED);
#endif
}
