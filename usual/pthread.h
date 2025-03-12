/*
 * Copyright (c) 2007-2009 Marko Kreen
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/** @file
 *
 * Pthreads compat for win32.
 */
#ifndef _USUAL_PTHREAD_H_
#define _USUAL_PTHREAD_H_

#include <usual/base.h>

#ifdef HAVE_PTHREAD_H
#include <pthread.h>

#else

#ifdef WIN32

#define pthread_create(a,b,c,d)		compat_pthread_create(a,b,c,d)
#define pthread_mutex_init(a,b)		compat_pthread_mutex_init(a,b)
#define pthread_mutex_destroy(a)	compat_pthread_mutex_destroy(a)
#define pthread_mutex_lock(a)		compat_pthread_mutex_lock(a)
#define pthread_mutex_unlock(a)		compat_pthread_mutex_unlock(a)
#define pthread_join(a,b)		compat_pthread_join(a,b)
#define pthread_key_create(a,b)     compat_pthread_key_create(a,b)
#define pthread_key_delete(a)       compat_pthread_key_delete(a)
#define pthread_getspecific(a)      compat_pthread_getspecific(a)
#define pthread_setspecific(a,b)    compat_pthread_setspecific(a,b)

typedef HANDLE pthread_t;
typedef HANDLE pthread_mutex_t;
typedef int pthread_attr_t;
typedef DWORD pthread_key_t;

int compat_pthread_create(pthread_t *t, pthread_attr_t *attr, void *(*fn)(void *), void *arg);
int compat_pthread_mutex_init(pthread_mutex_t *lock, void *unused);
int compat_pthread_mutex_destroy(pthread_mutex_t *lock);
int compat_pthread_mutex_lock(pthread_mutex_t *lock);
int compat_pthread_mutex_unlock(pthread_mutex_t *lock);
int compat_pthread_join(pthread_t *t, void **ret);
int compat_pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
int compat_pthread_key_delete(pthread_key_t key);
void* compat_pthread_getspecific(pthread_key_t key);
int compat_pthread_setspecific(pthread_key_t key, const void *value);



#endif /* WIN32 */

#endif /* HAVE_PTHREAD_H */

#endif
