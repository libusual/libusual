
#include <usual/hashing/memhash.h>
#include <usual/hashing/xxhash.h>
#include <usual/hashing/spooky.h>
#include <usual/crypto/csrandom.h>

#include <string.h>

uint32_t memhash_seed(const void *data, size_t len, uint32_t seed)
{
	if (sizeof(void *) == 8 || sizeof(long) == 8) {
		uint64_t hash[2];
		hash[0] = seed;
		hash[1] = 0;
		spookyhash(data, len, &hash[0], &hash[1]);
		return hash[0];
	} else {
		return xxhash(data, len, seed);
	}
}

uint32_t memhash(const void *data, size_t len)
{
	static bool initialized;
	static uint32_t rand_seed;

	if (!initialized) {
		initialized = true;
		rand_seed = csrandom();
	}
	return memhash_seed(data, len, rand_seed);
}

uint32_t memhash_string(const char *s)
{
	return memhash(s, strlen(s));
}

