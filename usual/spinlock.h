#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#ifdef WIN32
    #include <windows.h>
    #define ATOMIC_INT LONG
    #define THREAD_ID DWORD
    #define GET_THREAD_ID() GetCurrentThreadId()
#else
    #include <sched.h>
    #include <usual/pthread.h>
    #define ATOMIC_INT int
    #define THREAD_ID pthread_t
    #define GET_THREAD_ID() pthread_self()
#endif

typedef struct {
    ATOMIC_INT lock;
    THREAD_ID owner;
    int initialized;
} SpinLock;

void spin_lock_init(SpinLock *lock);
void spin_lock_acquire(SpinLock *lock);
void spin_lock_release(SpinLock *lock);

#endif /* _SPIN_LOCK_H_ */
