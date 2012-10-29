/*
 * Keccak implementation for SHA3 parameters.
 *
 * Copyright (c) 2012 Marko Kreen
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
 * Keccak with SHA3 parameters.
 */

#ifndef _USUAL_CRYPTO_KECCAK_H_
#define _USUAL_CRYPTO_KECCAK_H_

#include <usual/base.h>

/*
 * SHA3 fixed-length output modes.
 */

/** Output length for 224-bit mode (in bytes) */
#define KECCAK224_DIGEST_LENGTH (224/8)
/** Output length for 256-bit mode (in bytes) */
#define KECCAK256_DIGEST_LENGTH (256/8)
/** Output length for 384-bit mode (in bytes) */
#define KECCAK384_DIGEST_LENGTH (384/8)
/** Output length for 512-bit mode (in bytes) */
#define KECCAK512_DIGEST_LENGTH (512/8)

/** Number of data bytes processed in one loop. */
#define KECCAK224_BLOCK_SIZE (1152/8)
/** Number of data bytes processed in one loop. */
#define KECCAK256_BLOCK_SIZE (1088/8)
/** Number of data bytes processed in one loop. */
#define KECCAK384_BLOCK_SIZE (832/8)
/** Number of data bytes processed in one loop. */
#define KECCAK512_BLOCK_SIZE (576/8)

/** Number of data bytes processed in one go. */
#define KECCAK_STREAM_BLOCK_SIZE	(1024/8)

/**
 * Output length for stream mode (in bytes).
 *
 * This means output from single call to keccak_final().
 * It can be called repeatedly to get more output.
 */
#define KECCAK_STREAM_DIGEST_LENGTH	KECCAK_STREAM_BLOCK_SIZE

/**
 * Keccak state structure for all modes.
 */
struct KeccakContext {
	/* 5*5*64 bit state */
	union {
		uint64_t state64[25];
		uint32_t state32[2*25];
	} u;
	uint16_t bytes;  /* current number of bytes in buffer */
	uint16_t rbytes; /* number of bytes in one step */
	uint16_t obytes; /* output bytes */
	uint16_t padded; /* is padding added? */
};

/** SHA3 fixed length output mode.  */
void keccak224_init(struct KeccakContext *ctx);

/** SHA3 fixed length output mode.  */
void keccak256_init(struct KeccakContext *ctx);

/** SHA3 fixed length output mode.  */
void keccak384_init(struct KeccakContext *ctx);

/** SHA3 fixed length output mode.  */
void keccak512_init(struct KeccakContext *ctx);

/**
 * SHA3 stream mode for Keccak.
 *
 * In stream mode, keccak_final() can be called repeatedly
 * to get output stream of unlimited length.
 *
 * On each call it outputs next 128 bytes (1024 bits).
 */
void keccak_stream_init(struct KeccakContext *ctx);

/**
 * Hash additional data.
 */
void keccak_update(struct KeccakContext *ctx, const void *data, unsigned int len);

/**
 * Return final result.
 *
 * Output length depends on mode.  See KECCAK*_DIGEST_LENGTH
 * constants to get length for particular mode.
 *
 * In stream mode, this can be called repeatedly.
 */
void keccak_final(struct KeccakContext *ctx, uint8_t *dst);

#endif
