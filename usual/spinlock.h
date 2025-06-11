#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#include <string.h>

#ifdef WIN32
#   include <windows.h>
#   define GET_THREAD_ID() (GetCurrentThreadId()) 
#   define MEMORY_BARRIER() MemoryBarrier()
#   define THREAD_ID_EQUALS(a,b) a == b
#   define RESET_LOCK_WORD(a) InterlockedExchangePointer((PVOID*)&a, NULL);

#else
    #include <usual/pthread.h>
    #include <sched.h>
    #define GET_THREAD_ID() (pthread_self())
    #define MEMORY_BARRIER() __sync_synchronize()
    #define THREAD_ID_EQUALS(a,b) pthread_equal(a,b)
    #define RESET_LOCK_WORD(a) memset((void*)&a, 0, sizeof(pthread_t))
#endif

typedef struct {
#ifdef WIN32
    volatile LONG count;
    volatile DWORD lock_word;       // 0 = unlocked, otherwise holds thread ID
#else
    volatile int count;             // recursive depth
    volatile pthread_t lock_word;
#endif
    int initialized;
} SpinLock;

bool spin_lock_owns(SpinLock *lock);
void spin_lock_init(SpinLock *lock);
void spin_lock_acquire(SpinLock *lock);
void spin_lock_release(SpinLock *lock);

#endif /* _SPIN_LOCK_H_ */
