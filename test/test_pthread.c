#include "test_common.h"
#include <usual/pthread.h>


#define NUM_THREADS 4
static pthread_mutex_t lock;
static int shared_counter = 0;

static void *lock_func(void *arg) {
    pthread_mutex_lock(&lock);
    shared_counter += 1;
    pthread_mutex_unlock(&lock);
    return NULL;
}

static void test_pthread_mutex(void *p) {
    pthread_t threads[NUM_THREADS];

    tt_assert(pthread_mutex_init(&lock, NULL) == 0);

    for (int i = 0; i < NUM_THREADS; i++) {
        tt_assert(pthread_create(&threads[i], NULL, lock_func, NULL) == 0);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        tt_assert(pthread_join(threads[i], NULL) == 0);
    }

    tt_assert(shared_counter == NUM_THREADS);

    pthread_mutex_destroy(&lock);
    return;
end:;
}


static int thread_data[NUM_THREADS];
static pthread_key_t test_key;

static void test_pthread_key_destructor(void *value) {
    free(value);
}

static void *test_pthread_key_func(void *arg) {
    int thread_index = *(int *)arg;
    int *thread_specific_value = malloc(sizeof(int));
    int *retrieved;

    *thread_specific_value = thread_index;
    pthread_setspecific(test_key, thread_specific_value);
    usleep(1000);

    retrieved = pthread_getspecific(test_key);
    thread_data[thread_index] = *retrieved;
    return NULL;
}

static void test_pthread_key(void *p) {
    pthread_t threads[NUM_THREADS];
    
    tt_assert(pthread_key_create(&test_key, test_pthread_key_destructor) == 0);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i] = i;
        tt_assert(pthread_create(&threads[i], NULL, test_pthread_key_func, &thread_data[i]) == 0);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        tt_assert(pthread_join(threads[i], NULL) == 0);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        tt_assert(thread_data[i] == i);
    }
    tt_assert(pthread_key_delete(test_key) == 0);
    return;
end:;
}


struct testcase_t pthread_tests[] = {
    { "pthread_mutex", test_pthread_mutex },
    { "pthread_key", test_pthread_key },
    END_OF_TESTCASES
};
