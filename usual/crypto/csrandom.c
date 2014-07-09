/*
 * Cryptographically Secure Randomness.
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

#include <usual/crypto/csrandom.h>
#include <usual/crypto/entropy.h>
#include <usual/err.h>
#include <usual/string.h>
#include <usual/pthread.h>

#include <usual/crypto/keccak_prng.h>
#include <usual/crypto/chacha.h>

#ifdef HAVE_ARC4RANDOM_BUF

/*
 * Simply wrap arc4random_buf() API.
 */

uint32_t csrandom(void)
{
	return arc4random();
}

void csrandom_bytes(void *buf, size_t nbytes)
{
	arc4random_buf(buf, nbytes);
}

uint32_t csrandom_range(upper_bound)
{
	return arc4random_uniform(upper_bound);
}

#else /* !HAVE_ARC4RANDOM_BUF */

#define USE_KECCAK

#ifdef USE_KECCAK

/*
 * Keccak-based PRNG.
 */

static struct KeccakPRNG prng_keccak;

static void impl_init(void)
{
	char buf[32];

	if (getentropy(buf, sizeof(buf)) != 0)
		errx(1, "Cannot get system entropy");

	if (!keccak_prng_init(&prng_keccak, 576))
		errx(1, "Cannot initialize PRNG");
	keccak_prng_add_data(&prng_keccak, buf, sizeof(buf));

	explicit_bzero(buf, sizeof(buf));
}

static void impl_extract(void *buf, size_t nbytes)
{
	keccak_prng_extract(&prng_keccak, buf, nbytes);
}

#else

/*
 * ChaCha-based PRNG.
 */

static struct ChaCha prng_chacha;

static void impl_init(void)
{
	uint8_t buf[CHACHA_KEY_SIZE + CHACHA_IV_SIZE];

	if (getentropy(buf, sizeof(buf)) != 0)
		errx(1, "Cannot get system entropy");

	chacha_set_key_256(&prng_chacha, buf);
	chacha_set_nonce(&prng_chacha, 0, 0, buf + CHACHA_KEY_SIZE);

	explicit_bzero(buf, sizeof(buf));
}

static void impl_extract(void *buf, size_t nbytes)
{
	chacha_keystream(&prng_chacha, buf, nbytes);
}

#endif

/*
 * Locking
 */

static pthread_once_t once_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t prng_mutex;

static pid_t last_pid;
static int first_init_done;


#ifdef HAVE_PTHREAD_ATFORK
static void atfork_child(void)
{
	pthread_once_t tmp = PTHREAD_ONCE_INIT;
	memcpy(&once_init, &tmp, sizeof(tmp));
	last_pid = -1;
}
#endif

static void setup_locking(void)
{
	int err;
	char buf[128];

	last_pid = -1;

	/* reset lock */
	memset(&prng_mutex, 0, sizeof(prng_mutex));
	err = pthread_mutex_init(&prng_mutex, NULL);
	if (err != 0)
		errx(1, "csrandom lock init failed: %s", strerror_r(err, buf, sizeof(buf)));

	/* do the rest really only once */
	if (first_init_done)
		return;
	first_init_done = true;

#ifdef HAVE_PTHREAD_ATFORK
	pthread_atfork(NULL, NULL, atfork_child);
#endif
}

static void prng_lock(void)
{
	int err;
	char buf[128];

	err = pthread_mutex_lock(&prng_mutex);
	if (err != 0)
		errx(1, "csrandom lock failed: %s", strerror_r(err, buf, sizeof(buf)));
}

static void prng_unlock(void)
{
	int err;
	char buf[128];

	err = pthread_mutex_unlock(&prng_mutex);
	if (err != 0)
		errx(1, "csrandom unlock failed: %s", strerror_r(err, buf, sizeof(buf)));
}

/*
 * Make sure state is initialized.
 */

static void prng_check_and_lock(void)
{
	bool reseed = false;
	pid_t new_pid;

	pthread_once(&once_init, setup_locking);

	prng_lock();

	new_pid = getpid();
	if (new_pid != last_pid) {
		reseed = true;
		last_pid = new_pid;
	}

	if (reseed)
		impl_init();
}

/*
 * Public API follows
 */

void csrandom_bytes(void *buf, size_t nbytes)
{
	prng_check_and_lock();
	impl_extract(buf, nbytes);
	prng_unlock();
}

uint32_t csrandom(void)
{
	uint32_t val;
	csrandom_bytes(&val, sizeof(val));
	return val;
}

uint32_t csrandom_range(uint32_t upper_bound)
{
	uint32_t mod, lim, val;

	if (upper_bound <= 1)
		return 0;

	/* 2**32 % x == (2**32 - x) % x */
	mod = -upper_bound % upper_bound;

	/* wait for value in range [0 .. 2**32-mod) */
	lim = -mod;

	/* loop until good value appears */
	while (1) {
		val = csrandom();
		if (val < lim || lim == 0)
			return val % upper_bound;
	}
}

#endif /* !HAVE_ARC4RANDOM_BUF */

