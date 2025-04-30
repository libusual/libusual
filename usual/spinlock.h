#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#include <stdint.h>

#ifdef WIN32
    #include <windows.h>
    #define GET_THREAD_ID() ((uintptr_t)GetCurrentThreadId())
    #define MEMORY_BARRIER() MemoryBarrier()
#else
    #include <usual/pthread.h>
    #include <sched.h>
    #define GET_THREAD_ID() ((uintptr_t)pthread_self())
    #define MEMORY_BARRIER() __sync_synchronize()
#endif

typedef struct {
    volatile uintptr_t lock_word;  // 0 = unlocked, otherwise holds thread ID
    int count;                     // recursive depth
    int initialized;
} SpinLock;

void spin_lock_init(SpinLock *lock);
void spin_lock_acquire(SpinLock *lock);
void spin_lock_release(SpinLock *lock);

#endif /* _SPIN_LOCK_H_ */
