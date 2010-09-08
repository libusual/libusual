
#ifndef _USUAL_PGUTIL_H_
#define _USUAL_PGUTIL_H_

#include <usual/string.h>

bool pg_is_reserved_word(const char *str);

bool pg_quote_literal(char *_dst, const char *_src, int dstlen);
bool pg_quote_ident(char *_dst, const char *_src, int dstlen);
bool pg_quote_fqident(char *_dst, const char *_src, int dstlen);
struct StrList *pg_parse_array(const char *pgarr);

#endif

