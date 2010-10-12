/*
 * Copyright (c) 2009  Marko Kreen
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
 * Bit arithmetics.
 *
 * - is_power_of_2
 * - ffs, ffsl, ffsll
 * - fls, flsl, flsll
 * - rol16, rol32, rol64
 * - ror16, ror32, ror64
 */
#ifndef _USUAL_BITS_H_
#define _USUAL_BITS_H_

#include <usual/base.h>

#include <string.h>

/** Checks if integer has only one bit set */
static inline int is_power_of_2(int n)
{
	return (n > 0) && !(n & (n - 1));
}

/*
 * Single-eval and type-safe rol/ror
 */

/** Rotate 16-bit int to left */
static inline uint16_t rol16(uint16_t v, int s)
{
	return (v << s) | (v >> (16 - s));
}
/** Rotate 32-bit int to left */
static inline uint32_t rol32(uint32_t v, int s)
{
	return (v << s) | (v >> (32 - s));
}
/** Rotate 64-bit int to left */
static inline uint64_t rol64(uint64_t v, int s)
{
	return (v << s) | (v >> (64 - s));
}

/** Rotate 16-bit int to right */
static inline uint16_t ror16(uint16_t v, int s) { return rol16(v, 16 - s); }

/** Rotate 32-bit int to right */
static inline uint32_t ror32(uint32_t v, int s) { return rol32(v, 32 - s); }

/** Rotate 64-bit int to right */
static inline uint64_t ror64(uint64_t v, int s) { return rol64(v, 64 - s); }

/*
 * fls(int)
 * flsl(long)
 * flsll(long long)
 *
 *   find MSB bit set, 1-based ofs, 0 if arg == 0
 */

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define _FLS(sfx, type) \
	return (x == 0) ? 0 : ((8*sizeof(type)) - __builtin_clz ## sfx(x))
#else
#define _FLS(sfx, type) \
	unsigned type u = x; \
	unsigned int bit; \
	if (x == 0) return 0; \
	/* count from smallest bit, assuming small values */ \
	for (bit = 1; u > 1; bit++) u >>= 1; \
	return bit
#endif

#ifndef HAVE_FLS
#define fls(x) usual_fls(x)
/** Compat: Find last (MSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int fls(int x) { _FLS(, int); }
#endif
#ifndef HAVE_FLSL
#define flsl(x) usual_flsl(x)
/** Compat: Find last (MSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int flsl(long x) { _FLS(l, long); }
#endif
#ifndef HAVE_FLSLL
#define flsll(x) usual_flsll(x)
/** Compat: Find last (MSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int flsll(long long x) { _FLS(ll, long long); }
#endif
#undef _FLS

/*
 * ffs(int)
 * ffsl(long)
 * ffsll(long long)
 *
 *   find LSB bit set, 1-based ofs, 0 if arg == 0
 */

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define _FFS(sfx, type) \
	return __builtin_ffs ## sfx((unsigned type)(x))
#else
#define _FFS(sfx, type) \
	unsigned int bit; \
	unsigned type u = x; \
	if (!x) return 0; \
	/* count from smallest bit, assuming small values */ \
	for (bit = 1; !(u & 1); bit++) { \
		u >>= 1; \
	} \
	return bit
#endif

#ifndef HAVE_FFS
#define ffs(x) usual_ffs(x)
/** Compat: Find first (LSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int ffs(int x) { _FFS(, int); }
#endif
#ifndef HAVE_FFSL
#define ffsl(x) usual_ffsl(x)
/** Compat: Find first (LSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int ffsl(long x) { _FFS(l, long); }
#endif
#ifndef HAVE_FFSLL
#define ffsll(x) usual_ffsll(x)
/** Compat: Find first (LSB) set bit, 1-based ofs, 0 if arg == 0 */
static inline int ffsll(long long x) { _FFS(ll, long long); }
#endif
#undef _FFS

#endif

