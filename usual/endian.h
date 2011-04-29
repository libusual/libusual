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

/**
 * @file
 *
 * Endianess conversion macros.
 */

#ifndef _USUAL_ENDIAN_H_
#define _USUAL_ENDIAN_H_

#include <usual/base.h>

#ifdef HAVE_ENDIAN_H
#include <endian.h>
#endif
#ifdef HAVE_SYS_ENDIAN_H
#include <sys/endian.h>
#endif
#ifdef HAVE_BYTESWAP_H
#include <byteswap.h>
#endif

#include <string.h>

/**
 * @name  Always swap.
 * @{
 */

#ifndef bswap16
#ifdef bswap_16
#define bswap16(x) bswap_16(x)
#else
static inline uint16_t bswap16(uint16_t x)
{
	return (x << 8) | (x >> 8);
}
#endif
#endif

#ifndef bswap32
#ifdef bswap_32
#define bswap32(x) bswap_32(x)
#else
static inline uint32_t bswap32(uint32_t x)
{
#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
	return __builtin_bswap32(x);
#else
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0x00FF00FF);
	return (x << 16) | (x >> 16);
#endif
}
#endif
#endif

#ifndef bswap64
#ifdef bswap_64
#define bswap64(x) bswap_64(x)
#else
static inline uint64_t bswap64(uint64_t x)
{
	return ((uint64_t)bswap32(x) << 32) | bswap32(x >> 32);
}
#endif
#endif

/* @} */

/**
 * @name  Host <-> LE/BE
 * @{
 */

/* Ignore OS defines, as they may define only some subset of functions */
#undef htobe16
#undef htobe32
#undef htobe64
#undef htole16
#undef htole32
#undef htole64
#undef be16toh
#undef be32toh
#undef be64toh
#undef le16toh
#undef le32toh
#undef le64toh

#ifdef WORDS_BIGENDIAN

#define	htobe16(x)	((uint16_t)(x))
#define	htobe32(x)	((uint32_t)(x))
#define	htobe64(x)	((uint64_t)(x))
#define	htole16(x)	bswap16(x)
#define	htole32(x)	bswap32(x)
#define	htole64(x)	bswap64(x)

#define	be16toh(x)	((uint16_t)(x))
#define	be32toh(x)	((uint32_t)(x))
#define	be64toh(x)	((uint64_t)(x))
#define	le16toh(x)	bswap16(x)
#define	le32toh(x)	bswap32(x)
#define	le64toh(x)	bswap64(x)

#else

#define	htobe16(x)	bswap16(x)
#define	htobe32(x)	bswap32(x)
#define	htobe64(x)	bswap64(x)
#define	htole16(x)	((uint16_t)(x))
#define	htole32(x)	((uint32_t)(x))
#define	htole64(x)	((uint64_t)(x))

#define	be16toh(x)	bswap16(x)
#define	be32toh(x)	bswap32(x)
#define	be64toh(x)	bswap64(x)
#define	le16toh(x)	((uint16_t)(x))
#define	le32toh(x)	((uint32_t)(x))
#define	le64toh(x)	((uint64_t)(x))

#endif

/* @} */

#ifndef HAVE_ENCDEC_FUNCS

/**
 * @name Read LE/BE values from memory and convert to host format
 * @{
 */
static inline uint16_t be16dec(const void *p)
{
	uint16_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htobe16(tmp);
}
static inline uint32_t be32dec(const void *p)
{
	uint32_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htobe32(tmp);
}
static inline uint64_t be64dec(const void *p)
{
	uint64_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htobe64(tmp);
}
static inline uint16_t le16dec(const void *p)
{
	uint16_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htole16(tmp);
}
static inline uint32_t le32dec(const void *p)
{
	uint32_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htole32(tmp);
}
static inline uint64_t le64dec(const void *p)
{
	uint64_t tmp;
	memcpy(&tmp, p, sizeof(tmp));
	return htole64(tmp);
}
/* @} */

/**
 * @name Convert host value to LE/BE and write to memory
 * @{
 */
static inline void be16enc(void *p, uint16_t x)
{
	uint16_t tmp = htobe16(x);
	memcpy(p, &tmp, sizeof(tmp));
}
static inline void be32enc(void *p, uint32_t x)
{
	uint32_t tmp = htobe32(x);
	memcpy(p, &tmp, sizeof(tmp));
}
static inline void be64enc(void *p, uint64_t x)
{
	uint64_t tmp = htobe64(x);
	memcpy(p, &tmp, sizeof(tmp));
}
static inline void le16enc(void *p, uint16_t x)
{
	uint16_t tmp = htole16(x);
	memcpy(p, &tmp, sizeof(tmp));
}
static inline void le32enc(void *p, uint32_t x)
{
	uint32_t tmp = htole32(x);
	memcpy(p, &tmp, sizeof(tmp));
}
static inline void le64enc(void *p, uint64_t x)
{
	uint64_t tmp = htole64(x);
	memcpy(p, &tmp, sizeof(tmp));
}
/* @} */

#endif /* !HAVE_ENCDEC_FUNCS */

#endif	/* _USUAL_ENDIAN_H_ */
