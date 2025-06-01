#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#include <string.h>

#ifdef WIN32
#   include <windows.h>
#   define GET_THREAD_ID() ((uintptr_t)GetCurrentThreadId()) 
#   define MEMORY_BARRIER() MemoryBarrier()

#elif defined(__APPLE__)
#   include <pthread.h>
    static inline uintptr_t _darwin_tid(void)
    {
        uint64_t tid;
        /* always succeeds for current thread */
        (void)pthread_threadid_np(NULL, &tid);
        return (uintptr_t)tid;
    }
#   define GET_THREAD_ID() _darwin_tid()
#   define MEMORY_BARRIER() __sync_synchronize()

#else
#   include <sched.h>
#   include <unistd.h>
#   include <sys/types.h>
#   include <sys/syscall.h>
#   if defined(SYS_gettid)
        static inline uintptr_t _linux_tid(void)
        {
            return (uintptr_t)syscall(SYS_gettid);
        }
#       define GET_THREAD_ID() _linux_tid()
#   else        /* very old BSDs / exotic libc */
#       include <pthread.h>
        static inline uintptr_t _fallback_tid(void)
        {
            pthread_t self = pthread_self();
            uintptr_t id = 0;
            memcpy(&id, &self, sizeof(id));
            return id;
        }
#       define GET_THREAD_ID() _fallback_tid()
#   endif
#   define MEMORY_BARRIER() __sync_synchronize()
#endif /* platform switch */

typedef struct {
    volatile uintptr_t lock_word;  // 0 = unlocked, otherwise holds thread ID
    volatile int count;            // recursive depth
    int initialized;
} SpinLock;

void spin_lock_init(SpinLock *lock);
void spin_lock_acquire(SpinLock *lock);
void spin_lock_release(SpinLock *lock);

#endif /* _SPIN_LOCK_H_ */
