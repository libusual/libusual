/*
 * Pthreads compat.
 *
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


#include <usual/pthread.h>

#ifndef HAVE_PTHREAD_H
#ifdef WIN32
/*
 * basic pthreads for win32.
 */

struct _w32thread {
	void *(*fn)(void *);
	void *arg;
};

static DWORD WINAPI w32launcher(LPVOID arg)
{
	struct _w32thread *info = arg;
	info->fn(info->arg);
	free(info);
	return 0;
}

int compat_pthread_create(pthread_t *t, pthread_attr_t *attr, void *(*fn)(void *), void *arg)
{
	struct _w32thread *info = calloc(1, sizeof(*info));
	if (!info)
		return -1;
	info->fn = fn;
	info->arg = arg;
	*t = CreateThread(NULL, 0, w32launcher, info, 0, NULL);
	if (*t == NULL)
		return -1;
	return 0;
}

int compat_pthread_join(pthread_t *t, void **ret)
{
	if (WaitForSingleObject(*t, INFINITE) != WAIT_OBJECT_0)
		return -1;
	CloseHandle(*t);
	return 0;
}

int compat_pthread_mutex_init(pthread_mutex_t *lock, void *unused)
{
	*lock = CreateMutex(NULL, FALSE, NULL);
	if (*lock == NULL)
		return -1;
	return 0;
}

int compat_pthread_mutex_destroy(pthread_mutex_t *lock)
{
	if (*lock) {
		CloseHandle(*lock);
		*lock = NULL;
	}
	return 0;
}

int compat_pthread_mutex_lock(pthread_mutex_t *lock)
{
	if (WaitForSingleObject(*lock, INFINITE) != WAIT_OBJECT_0)
		return -1;
	return 0;
}

int compat_pthread_mutex_unlock(pthread_mutex_t *lock)
{
	if (!ReleaseMutex(*lock))
		return -1;
	return 0;
}

int compat_pthread_key_create(pthread_key_t *key, void (*destructor)(void*))
{
	if (!key) return EINVAL;
	*key = TlsAlloc();
	return (*key == TLS_OUT_OF_INDEXES) ? EINVAL : 0;
}

int compat_pthread_key_delete(pthread_key_t key)
{
	return FlsFree(key) == true ? 0 : EINVAL;
}

void* compat_pthread_getspecific(pthread_key_t key)
{
	return TlsGetValue(key);
}

int compat_pthread_setspecific(pthread_key_t key, const void *value)
{
	return TlsSetValue(key, (LPVOID)value) ? 0 : EINVAL;
}



#endif /* win32 */
#endif /* !HAVE_PTHREAD_H */
