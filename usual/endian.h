/*
 * Endianess comversion macros.
 *
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

/*
 * Always swap:
 *	bswap16, bswap32, bswap64
 *
 * Host <> LE/BE
 *	htobe16, htobe32, htobe64
 *	htole16, htole32, htole64
 *	be16toh, be32toh, be64toh
 *	le16toh, le32toh, le64toh
 *
 * Read LE/BE -> Host:
 *	le16dec, le32dec, le64dec
 *	be16dec, be32dec, be64dec
 *
 * Write Host -> LE/BE:
 *	le16enc, le32enc, le64enc
 *	be16enc, be32enc, be64enc
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

/*
 * Always swap.
 */

#ifndef bswap16
#ifdef bswap_16
#define bswap16(x) bswap_16(x)
#else
static inline uint16_t _gen_bswap16(uint16_t x)
{
	return (x << 8) | (x >> 8);
}
#define bswap16(x) _gen_bswap16(x)
#endif
#endif

#ifndef bswap32
#ifdef bswap_32
#define bswap32(x) bswap_32(x)
#else
static inline uint32_t _gen_bswap32(uint32_t x)
{
#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
	return __builtin_bswap32(x);
#else
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0x00FF00FF);
	return (x << 16) | (x >> 16);
#endif
}
#define bswap32(x) _gen_bswap32(x)
#endif
#endif

#ifndef bswap64
#ifdef bswap_64
#define bswap64(x) bswap_64(x)
#else
static inline uint64_t _gen_bswap64(uint64_t x)
{
	return ((uint64_t)bswap32(x) << 32) | bswap32(x >> 32);
}
#define bswap64(x) _gen_bswap64(x)
#endif
#endif

/*
 * Host <-> LE/BE
 */

#ifndef le64toh

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

#endif

/*
 * Read LE/BE values from memory.
 */

#define _DEC(name, typ, decode) \
static inline typ name(const void *p) { \
	typ tmp; \
	memcpy(&tmp, p, sizeof(typ)); \
	return decode(tmp); \
}

_DEC(be16dec, uint16_t, be16toh)
_DEC(be32dec, uint32_t, be32toh)
_DEC(be64dec, uint64_t, be64toh)
_DEC(le16dec, uint16_t, le16toh)
_DEC(le32dec, uint32_t, le32toh)
_DEC(le64dec, uint64_t, le64toh)
#undef _DEC

/*
 * Write LE/BE values to memory.
 */

#define _ENC(name, typ, encode) \
static inline void name(void *p, typ val) { \
	typ tmp = encode(val); \
	memcpy(p, &tmp, sizeof(typ)); \
}
_ENC(be16enc, uint16_t, htobe16)
_ENC(be32enc, uint32_t, htobe32)
_ENC(be64enc, uint64_t, htobe64)
_ENC(le16enc, uint16_t, htole16)
_ENC(le32enc, uint32_t, htole32)
_ENC(le64enc, uint64_t, htole64)
#undef _ENC

#endif	/* _USUAL_ENDIAN_H_ */
