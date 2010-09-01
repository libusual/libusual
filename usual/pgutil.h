
#ifndef _USUAL_PGUTIL_H_
#define _USUAL_PGUTIL_H_

#include <usual/string.h>

enum PgKeywordType {
	PG_NOT_KEYWORD = 0,
	PG_UNRESERVED_KEYWORD = 1,
	PG_RESERVED_KEYWORD = 2,
	PG_TYPE_FUNC_NAME_KEYWORD = 3,
	PG_COL_NAME_KEYWORD = 4
};
enum PgKeywordType pg_keyword_lookup(const char *str);

bool pg_is_reserved_word(const char *str);

bool pg_quote_literal(char *_dst, const char *_src, int dstlen);
bool pg_quote_ident(char *_dst, const char *_src, int dstlen);
bool pg_quote_fqident(char *_dst, const char *_src, int dstlen);
struct StrList *parse_pgarray(const char *pgarr);

#endif

