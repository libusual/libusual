/*
 * Load entropy.
 *
 * Copyright (c) 2014  Marko Kreen
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

#include <usual/crypto/entropy.h>
#include <usual/err.h>
#include <usual/string.h>

#ifndef HAVE_GETENTROPY

/*
 * Load system entropy.
 */

#if defined(_WIN32) || defined(_WIN64)

/*
 * Windows
 *
 * It's possible to get entropy via:
 * - CryptGenRandom.  Uses RtlGenRandom, requires CryptoAPI.
 * - rand_s().  Uses RtlGenRandom,  Requires VS2005 CRT, WindowsXP+.
 *   Missing in mingw32, exists in mingw64.
 * - RtlGenRandom().  Internal func, no proper public definition.
 *   There is broken def in <ntsecapi.h> that does not have NTAPI.
 *   Need to link or load from advapi32.dll.
 */

typedef BOOLEAN APIENTRY (*rtlgenrandom_t)(void *, ULONG);

int getentropy(void *dst, size_t len)
{
	HMODULE lib;
	rtlgenrandom_t fn;
	int res = -1;

	lib = LoadLibrary("advapi32.dll");
	if (lib) {
		fn = (rtlgenrandom_t)GetProcAddress(lib, "SystemFunction036");
		if (fn && fn(dst, len))
			res = 0;
		FreeLibrary(lib);
	}
	if (res < 0)
		errno = EIO;
	return res;
}

#elif defined(HAVE_GETRANDOM)

int getentropy(void *dst, size_t len)
{
	int res;

	if (len > 256)
		goto eio;
	res = getrandom(dst, len, 0);
	if (res < 0)
		return -1;
	if (res == len)
		return 0;
eio:
	errno = EIO;
	return -1;
}

#else /* UNIX-like system */

#include <sys/stat.h>
#include <fcntl.h>

/* open and check device node */
static int open_devrandom(const char *dev)
{
	int fd;
	int oflags = O_RDONLY;
#ifdef O_CLOEXEC
	oflags |= O_CLOEXEC;
#endif

open_loop:
	fd = open(dev, oflags);
	if (fd == -1) {
		if (errno == EINTR)
			goto open_loop;
		return -1;
	}

#ifndef O_CLOEXEC
	fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
#endif

	/*
	 * Lightly verify that the device node looks sane
	 */

	{
		struct stat st;
		if (fstat(fd, &st) == -1 || !S_ISCHR(st.st_mode))
			goto fail;
	}
#ifdef RNDGETENTCNT
	{
		int cnt;
		if (ioctl(fd, RNDGETENTCNT, &cnt) == -1)
			goto fail;
	}
#endif

	/* seems fine */
	return fd;

fail:
	close(fd);
	return -1;
}

/*
 * Read normal random devices under /dev.
 */

static const char *devlist[] = {
	"/dev/urandom",
	"/dev/random",
	NULL,
};

int getentropy(void *dst, size_t bytes)
{
	uint8_t *d = dst;
	size_t need = bytes;
	int fd, res;
	unsigned int i;

	for (i = 0; devlist[i]; i++) {
	reopen:
		fd = open_devrandom(devlist[i]);
		if (fd == -1)
			continue;

		while (need > 0) {
			res = read(fd, d, need);
			if (res > 0) {
				/* successful read */
				need -= res;
				d += res;
			} else if (res == 0) {
				/* eof - open again */
				close(fd);
				goto reopen;
			} else if (errno == EINTR) {
				/* signal - retry read */
			} else {
				close(fd);
				/* random error, fail */
				return -1;
			}
		}
		close(fd);
		return 0;
	}

	errno = EIO;
	return -1;
}

#endif /* unix */

#endif /* !HAVE_GETENTROPY */

