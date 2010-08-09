#ifndef _USUAL_MDICT_H_
#define _USUAL_MDICT_H_

#include <usual/cxalloc.h>
#include <usual/mbuf.h>

struct MDict;

struct MDict *mdict_new(CxMem *cx);
void mdict_free(struct MDict *dict);

bool mdict_urldecode(struct MDict *dict, const char *str, unsigned len);
bool mdict_urlencode(struct MDict *dict, struct MBuf *dst);

const struct MBuf *mdict_get_buf(struct MDict *dict, const char *key, unsigned klen);
const char *mdict_get_str(struct MDict *dict, const char *key, unsigned klen);
bool mdict_put_str(struct MDict *dict, const char *key, unsigned klen, const char *val, unsigned vlen);

typedef bool (*mdict_walker_f)(void *arg, const struct MBuf *k, const struct MBuf *v);
bool mdict_walk(struct MDict *dict, mdict_walker_f cb_func, void *cb_arg);

/*
 * Simple API that calculates strlen inline.
 */

static inline const char *mdict_get(struct MDict *dict, const char *key)
{
	return mdict_get_str(dict, key, strlen(key));
}

static inline bool mdict_put(struct MDict *dict, const char *key, const char *val)
{
	unsigned klen = strlen(key);
	unsigned vlen = val ? strlen(val) : 0;
	return mdict_put_str(dict, key, klen, val, vlen);
}

static inline bool mdict_put_buf(struct MDict *dict, const char *key, const struct MBuf *buf)
{
	unsigned klen = strlen(key);
	const char *val = buf ? mbuf_data(buf) : NULL;
	unsigned vlen = buf ? mbuf_written(buf) : 0;
	return mdict_put_str(dict, key, klen, val, vlen);
}

#endif

