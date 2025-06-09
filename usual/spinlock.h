#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#include <string.h>

#ifdef WIN32
#   include <windows.h>
#   define GET_THREAD_ID() ((uintptr_t)GetCurrentThreadId()) 
#   define MEMORY_BARRIER() MemoryBarrier()

#elif defined(HAVE_PTHREAD_THREADID_NP) && HAVE_PTHREAD_THREADID_NP
#   include <pthread.h>
    static inline uintptr_t _pthread_tid(void)
    {
        uint64_t tid;
        /* always succeeds for current thread */
        (void)pthread_threadid_np(NULL, &tid);
        return (uintptr_t)tid;
    }
#   define GET_THREAD_ID() _pthread_tid()
#   define MEMORY_BARRIER() __sync_synchronize()

#else
#   include <unistd.h>
#   define GET_THREAD_ID() gettid()
#   define MEMORY_BARRIER() __sync_synchronize()
#endif

typedef struct {
    volatile uintptr_t lock_word;  // 0 = unlocked, otherwise holds thread ID
    volatile int count;            // recursive depth
    int initialized;
} SpinLock;

void spin_lock_init(SpinLock *lock);
void spin_lock_acquire(SpinLock *lock);
void spin_lock_release(SpinLock *lock);

#endif /* _SPIN_LOCK_H_ */
