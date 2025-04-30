#include <usual/logging.h>
#include <usual/spinlock.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SPIN_LOCK_INITIALIZED 1

void spin_lock_init(SpinLock *lock) {
    lock->lock_word = 0;
    lock->count = 0;
    lock->initialized = SPIN_LOCK_INITIALIZED;
}

void spin_lock_acquire(SpinLock *lock) {
    if (lock->initialized != SPIN_LOCK_INITIALIZED)
        fatal("Attempt to acquire an uninitialized lock!");

    uintptr_t self = GET_THREAD_ID();

    if (lock->lock_word == self) {
        lock->count++;
        return;
    }

    while (!__sync_bool_compare_and_swap(&lock->lock_word, 0, self)) {
        sched_yield();
    }

    MEMORY_BARRIER();
    lock->count = 1;
}

void spin_lock_release(SpinLock *lock) {
    if (lock->initialized != SPIN_LOCK_INITIALIZED)
        fatal("Attempt to acquire an uninitialized lock!");

    uintptr_t self = GET_THREAD_ID();

    if (lock->lock_word != self) {
        fatal("Thread %lu tried to release a lock it does not own!", (unsigned long)GET_THREAD_ID());
    }

    if (--lock->count == 0) {
        MEMORY_BARRIER();
        lock->lock_word = 0;
    }
}
