
#ifndef _USUAL_HASHING_MEMHASH_H_
#define _USUAL_HASHING_MEMHASH_H_

#include <usual/base.h>

uint32_t memhash(const void *data, size_t len);
uint32_t memhash_string(const char *s);
uint32_t memhash_seed(const void *data, size_t len, uint32_t seed);

#endif

