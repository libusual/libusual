/*
 * PRNG based on Keccak.
 */


#include <usual/crypto/keccak_prng.h>

bool keccak_prng_init(struct KeccakPRNG *prng, int capacity)
{
	if (!keccak_init(&prng->ctx, capacity))
		return false;
	prng->extracting = false;
	prng->have_data = false;
	return true;
}

void keccak_prng_add_data(struct KeccakPRNG *prng, const void *data, size_t len)
{
	if (prng->extracting) {
		keccak_rewind(&prng->ctx);
		prng->extracting = false;
	}

	keccak_absorb(&prng->ctx, data, len);

	if (!prng->have_data && len > 0)
		prng->have_data = true;
}

bool keccak_prng_extract(struct KeccakPRNG *prng, void *data, size_t len)
{
	if (!prng->have_data)
		return false;
	if (!prng->extracting) {
		keccak_pad(&prng->ctx, "\x01", 1);
		prng->extracting = true;
	}
	keccak_squeeze(&prng->ctx, data, len);
	return true;
}

