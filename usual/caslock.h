#ifndef _CAS_LOCK_H_
#define _CAS_LOCK_H_

#ifdef WIN32
    #include <windows.h>
    #define ATOMIC_INT LONG
#else
    #include <stdatomic.h>
    #define ATOMIC_INT _Atomic int
#endif


typedef struct {
    ATOMIC_INT lock;
} Cas_Lock;


static inline void cas_lock_init(Cas_Lock *lock) {
#ifdef WIN32
    InterlockedExchange(&lock->lock, 0);
#else
    atomic_store(&lock->lock, 0);
#endif
}


static inline void cas_lock_acquire(Cas_Lock *lock) {
#ifdef WIN32
    while (InterlockedCompareExchange(&lock->lock, 1, 0) != 0) {
        // Spin until we acquire the lock
    }
#else
    int expected = 0;
    while (!atomic_compare_exchange_weak(&lock->lock, &expected, 1)) {
        expected = 0;
    }
#endif
}


static inline void cas_lock_release(Cas_Lock *lock) {
#ifdef WIN32
    InterlockedExchange(&lock->lock, 0);
#else
    atomic_store(&lock->lock, 0);
#endif
}


static inline void cas_lock_destroy(Cas_Lock *lock) {
    // No cleanup required
}

#endif /* _CAS_LOCK_H_ */
