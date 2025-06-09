#include <usual/logging.h>
#include <usual/spinlock.h>

#define SPIN_LOCK_INITIALIZED 1

void spin_lock_init(SpinLock *lock) {
    lock->lock_word = 0;
    lock->count = 0;
    lock->initialized = SPIN_LOCK_INITIALIZED;
}

void spin_lock_acquire(SpinLock *lock) {
    uintptr_t self;

    if (lock->initialized != SPIN_LOCK_INITIALIZED)
        fatal("Attempt to acquire an uninitialized lock!");

    self = GET_THREAD_ID();

    if (lock->lock_word == self) {
        lock->count++;
        return;
    }

#ifdef WIN32
    while (InterlockedCompareExchangePointer((PVOID*)&lock->lock_word, (PVOID)self, NULL) != NULL) {
        SwitchToThread();
    }
#else
    #include <sched.h>
    while (!__sync_bool_compare_and_swap(&lock->lock_word, 0, self)) {
        sched_yield();
    }
#endif

    MEMORY_BARRIER();
    lock->count = 1;
}

void spin_lock_release(SpinLock *lock) {
    uintptr_t self;

    if (lock->initialized != SPIN_LOCK_INITIALIZED)
        fatal("Attempt to release an uninitialized lock!");

    self = GET_THREAD_ID();

    if (lock->lock_word != self) {
        fatal("Thread %lu tried to release a lock it does not own!", (unsigned long)self);
    }

    if (--lock->count == 0) {
        MEMORY_BARRIER();
#ifdef WIN32
        InterlockedExchangePointer((PVOID*)&lock->lock_word, NULL);
#else
        lock->lock_word = 0;
#endif
    }
}
