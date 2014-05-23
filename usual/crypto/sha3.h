/*
 * SHA3 implementation.
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

#ifndef _USUAL_CRYPTO_SHA3_H_
#define _USUAL_CRYPTO_SHA3_H_

#include <usual/crypto/keccak.h>

#define SHA3_224_CAPACITY	448
#define SHA3_256_CAPACITY	512
#define SHA3_384_CAPACITY	768
#define SHA3_512_CAPACITY	1024
#define SHAKE128_CAPACITY	256
#define SHAKE256_CAPACITY	512

#define SHA3_224_DIGEST_LENGTH	(224/8)
#define SHA3_256_DIGEST_LENGTH	(256/8)
#define SHA3_384_DIGEST_LENGTH	(384/8)
#define SHA3_512_DIGEST_LENGTH	(512/8)
#define SHAKE128_DIGEST_LENGTH	(256/8)
#define SHAKE256_DIGEST_LENGTH	(512/8)

#define SHA3_224_BLOCK_SIZE	((1600 - SHA3_224_CAPACITY) / 8)
#define SHA3_256_BLOCK_SIZE	((1600 - SHA3_256_CAPACITY) / 8)
#define SHA3_384_BLOCK_SIZE	((1600 - SHA3_384_CAPACITY) / 8)
#define SHA3_512_BLOCK_SIZE	((1600 - SHA3_512_CAPACITY) / 8)
#define SHAKE128_BLOCK_SIZE	((1600 - SHAKE128_CAPACITY) / 8)
#define SHAKE256_BLOCK_SIZE	((1600 - SHAKE256_CAPACITY) / 8)

struct SHA3Context {
	struct KeccakContext kctx;
	bool padded;
	uint8_t pad;
	unsigned int obytes;
};

void sha3_224_reset(struct SHA3Context *ctx);
void sha3_256_reset(struct SHA3Context *ctx);
void sha3_384_reset(struct SHA3Context *ctx);
void sha3_512_reset(struct SHA3Context *ctx);
void sha3_update(struct SHA3Context *ctx, const void *ptr, unsigned len);
void sha3_final(struct SHA3Context *ctx, void *dst);

void shake128_reset(struct SHA3Context *ctx);
void shake256_reset(struct SHA3Context *ctx);
void shake_update(struct SHA3Context *ctx, const void *ptr, unsigned len);
void shake_extract(struct SHA3Context *ctx, void *dst, unsigned count);

#endif

