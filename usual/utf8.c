/*
 * Low-level UTF8 handling.
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

#include <usual/utf8.h>

#define u8head(c, mask)	(((c) & (mask | (mask >> 1))) == mask)
#define u8tail(c)	u8head(c, 0x80)

/*
 * conservative utf8 decoder
 *
 * if invalid char, advance src pointer by one and return 0.
 * this can be ignored or replaced.
 */
uint32_t utf8_get_char(const uint8_t **src_p, const uint8_t *srcend)
{
	uint32_t c;
	const uint8_t *p = *src_p;
	/*
	 * 0xxx xxxx -> len=1
	 * 10xx xxxx -> tail byte
	 * 110x xxxx -> len=2
	 * 1110 xxxx -> len=3
	 * 1111 0xxx -> len=4
	 */
	if (p[0] < 0x80) {
		c = *p++;
	} else if (u8head(p[0], 0xC0)) {
		if (p + 2 > srcend)
			goto eos;
		if (!u8tail(p[1]))
			goto bad_enc;

		c = ((p[0] & 0x1F) << 6) | (p[1] & 0x3F);
		if (c < 0x80)
			goto bad_enc;
		p += 2;
	} else if (u8head(p[0], 0xE0)) {
		if (p + 3 > srcend)
			goto eos;
		if (!u8tail(p[1]) || !u8tail(p[2]))
			goto bad_enc;

		c = ((p[0] & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
		if ((c < 0x800) || ((c & 0xF800) == 0xD800))
			goto bad_enc;
		p += 3;
	} else if (u8head(p[0], 0xF0)) {
		if (p + 4 > srcend)
			goto eos;
		if (!u8tail(p[1]) || !u8tail(p[2]) || !u8tail(p[3]))
			goto bad_enc;

		c = ((p[0] & 0x1F) << 18) | ((p[1] & 0x3F) << 12)
		  | ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
		if (c < 0x10000 || c > 0x10FFFF)
			goto bad_enc;
		p += 4;
	} else {
		goto bad_enc;
	}
	*src_p = p;
	return c;
bad_enc:
	*src_p = p + 1;
	return 0;
eos:
	*src_p = srcend;
	return 0;
}

/* encode one char - skip invalid ones */
bool utf8_put_char(uint32_t c, uint8_t **dst_p, const uint8_t *dstend)
{
	uint8_t *dst = *dst_p;
	if (c < 0x80) {
		if (dst + 1 > dstend)
			goto no_room;
		*dst++ = c;
	} else if (c < 0x800) {
		if (dst + 2 > dstend)
			goto no_room;
		*dst++ = 0xC0 | (c >> 6);
		*dst++ = 0x80 | (c & 0x3F);
	} else if (c < 0x00010000) {
		if (dst + 3 > dstend)
			goto no_room;
		if (c < 0xD800 || c > 0xDFFF) {
			*dst++ = 0xE0 | (c >> 12);
			*dst++ = 0x80 | ((c >> 6) & 0x3F);
			*dst++ = 0x80 | (c & 0x3F);
		}
	} else if (c <= 0x10FFFF) {
		if (dst + 4 > dstend)
			goto no_room;
		*dst++ = 0xF0 | (c >> 18);
		*dst++ = 0x80 | ((c >> 12) & 0x3F);
		*dst++ = 0x80 | ((c >> 6) & 0x3F);
		*dst++ = 0x80 | (c & 0x3F);
	}
	*dst_p = dst;
	return true;

no_room:
	return false;
}

unsigned utf8_char_size(uint32_t c)
{
	if (c < 0x80) return 1;
	if (c < 0x800) return 2;
	if (c < 0x1000) return 3;
	return 4;
}

unsigned utf8_seq_size(uint8_t b)
{
	if (b < 0x80) return 1;
	if (b < 0xC0) return 0;
	if (b < 0xE0) return 2;
	if (b < 0xF0) return 3;
	if (b < 0xF8) return 4;
	return 0;
}

