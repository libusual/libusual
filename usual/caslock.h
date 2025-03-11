#ifndef _CAS_LOCK_H_
#define _CAS_LOCK_H_

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
} CasLock;

void cas_lock_init(CasLock *lock);
void cas_lock_acquire(CasLock *lock);
void cas_lock_release(CasLock *lock);

#endif /* _CAS_LOCK_H_ */
