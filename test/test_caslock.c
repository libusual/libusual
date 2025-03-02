#include <usual/caslock.h>
#include <usual/pthread.h>
#include "test_common.h"

/*
 * Basic acquire and release test
 */
static void test_cas_lock_basic(void *p)
{
    CasLock lock;
    cas_lock_init(&lock);

    cas_lock_acquire(&lock);
    int_check(lock.lock, 1);

    cas_lock_release(&lock);
    int_check(lock.lock, 0);

end:;
}

/*
 * Multithreading stress test
 */
#define NUM_THREADS 10
#define NUM_ITERATIONS 10000

static CasLock shared_lock;
static int shared_counter = 0;

static void *thread_function(void *arg)
{
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        cas_lock_acquire(&shared_lock);
        shared_counter++;
        cas_lock_release(&shared_lock);
    }
    return NULL;
}

static void test_cas_lock_multithreaded(void *p)
{
    pthread_t threads[NUM_THREADS];
    cas_lock_init(&shared_lock);
    shared_counter = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int_check(shared_counter, NUM_THREADS * NUM_ITERATIONS);
end:;
}

/*
 * Describe test cases
 */
struct testcase_t caslock_tests[] = {
    { "basic", test_cas_lock_basic },
    { "multithread", test_cas_lock_multithreaded },
    END_OF_TESTCASES
};
