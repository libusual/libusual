#ifndef _USUAL_CRYPTO_KECCAK_PRNG_H_
#define _USUAL_CRYPTO_KECCAK_PRNG_H_

#include <usual/crypto/keccak.h>

/*
 * PRNG based on Keccak.
 */

struct KeccakPRNG {
	struct KeccakContext ctx;
	bool extracting;
	bool have_data;
};

bool keccak_prng_init(struct KeccakPRNG *prng, int capacity);
void keccak_prng_add_data(struct KeccakPRNG *prng, const void *data, size_t len);
bool keccak_prng_extract(struct KeccakPRNG *prng, void *data, size_t len);

#endif
