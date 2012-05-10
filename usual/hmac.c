/*
 * HMAC-SHA1 implementation based on OpenBSD hmac.c
 *
 * Copyright (c) 2012 Daniel Farina
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

#include <usual/hmac.h>
#include <usual/sha1.h>

#include <string.h>

/* Clean HMAC-SHA1 state */
void
hmac_sha1_reset(struct hmac_sha1_ctx *ctx,
		const uint8_t *key, unsigned int key_len)
{
	uint8_t k_ipad[SHA1_BLOCK_SIZE];
	int i;

	if (key_len > SHA1_BLOCK_SIZE) {
		sha1_reset(&ctx->ctx);
		sha1_update(&ctx->ctx, key, key_len);
		sha1_final(ctx->key, &ctx->ctx);
		ctx->key_len = SHA1_DIGEST_LENGTH;
	} else {
		memcpy(ctx->key, key, key_len);
		ctx->key_len = key_len;
	}

	memset(k_ipad, 0, sizeof k_ipad);
	memcpy(k_ipad, ctx->key, ctx->key_len);

	for (i = 0; i < SHA1_BLOCK_SIZE; i += 1)
		k_ipad[i] ^= 0x36;

	sha1_reset(&ctx->ctx);
	sha1_update(&ctx->ctx, k_ipad, SHA1_BLOCK_SIZE);

	/*
	 * Seen in OpenBSD source, presumably to prevent key leakage through
	 * uninitialized memory.
	 */
	memset(k_ipad, 0, sizeof k_ipad);
}


/* Update HMAC-SHA1 state with more data */
void
hmac_sha1_update(struct hmac_sha1_ctx *ctx,
		 const void *data, unsigned int len)
{
	sha1_update(&ctx->ctx, data, len);
}


/* Get final HMAC-SHA1 result */
void hmac_sha1_final(uint8_t *dst, struct hmac_sha1_ctx *ctx)
{
	uint8_t k_opad[SHA1_BLOCK_SIZE];
	int i;

	sha1_final(dst, &ctx->ctx);

	memset(k_opad, 0, sizeof k_opad);
	memcpy(k_opad, ctx->key, ctx->key_len);
	for (i = 0; i < SHA1_BLOCK_SIZE; i += 1)
		k_opad[i] ^= 0x5c;

	sha1_reset(&ctx->ctx);
	sha1_update(&ctx->ctx, k_opad, SHA1_BLOCK_SIZE);
	sha1_update(&ctx->ctx, dst, SHA1_DIGEST_LENGTH);
	sha1_final(dst, &ctx->ctx);

	/*
	 * Seen in OpenBSD source, presumably to prevent key leakage through
	 * uninitialized memory.
	 */
	memset(k_opad, 0, sizeof k_opad);
}
