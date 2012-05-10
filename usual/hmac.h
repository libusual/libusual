/*
 * HMAC implementation based on OpenBSD
 *
 * Copyright (c) 2012  Daniel Farina
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
 * HMAC-SHA1 implementation (RFC2104).
 */

#ifndef _USUAL_HMAC_H_
#define _USUAL_HMAC_H_

#include <usual/base.h>

#include <usual/sha1.h>

/** HMAC-SHA1 Context */
struct hmac_sha1_ctx {
	struct	sha1_ctx	ctx;
	uint8_t			key[SHA1_BLOCK_SIZE];
	unsigned int		key_len;
};

/** Initialize context with new key */
void hmac_sha1_reset(struct hmac_sha1_ctx *ctx, const uint8_t *key, unsigned int key_len);

/** Hash more data */
void hmac_sha1_update(struct hmac_sha1_ctx *ctx, const void *data, unsigned int len);

/** Get final result */
void hmac_sha1_final(uint8_t *dst, struct hmac_sha1_ctx *ctx);

#endif /* _USUAL_HMAC_H_ */
