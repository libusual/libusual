
#include <usual/pgutil.h>

#include "test_common.h"

/*
 * pg_quote_literal
 */

static char *run_quote_lit(char *dst, const char *src, int size)
{
	if (pg_quote_literal(dst, src, size))
		return dst;
	return "FAIL";
}

static void test_quote_lit(void *ptr)
{
	char buf[128];
	str_check(run_quote_lit(buf, "", 16), "''");
	str_check(run_quote_lit(buf, "a", 16), "'a'");
	str_check(run_quote_lit(buf, "a'a", 16), "'a''a'");
	str_check(run_quote_lit(buf, "a\\a", 16), "E'a\\\\a'");

	str_check(run_quote_lit(buf, "", 3), "''");
	str_check(run_quote_lit(buf, "", 2), "FAIL");
	str_check(run_quote_lit(buf, "", 1), "FAIL");
	str_check(run_quote_lit(buf, "", 0), "FAIL");

	str_check(run_quote_lit(buf, "a'a", 7), "'a''a'");
	str_check(run_quote_lit(buf, "a'a", 6), "FAIL");

	str_check(run_quote_lit(buf, "a\\a", 8), "E'a\\\\a'");
	str_check(run_quote_lit(buf, "a\\a", 7), "FAIL");

	str_check(run_quote_lit(buf, "a", 4), "'a'");
	str_check(run_quote_lit(buf, "a", 3), "FAIL");
end:;
}

/*
 * quote_ident
 */

static char *qident(char *dst, const char *src, int size)
{
	if (pg_quote_ident(dst, src, size))
		return dst;
	return "FAIL";
}

static void test_quote_ident(void *ptr)
{
	char buf[128];
	str_check(qident(buf, "", 16), "\"\"");
	str_check(qident(buf, "id_", 16), "id_");
	str_check(qident(buf, "_id", 16), "_id");
	str_check(qident(buf, "Baz", 16), "\"Baz\"");
	str_check(qident(buf, "baZ", 16), "\"baZ\"");
	str_check(qident(buf, "b z", 16), "\"b z\"");
	str_check(qident(buf, "5id", 16), "\"5id\"");
	str_check(qident(buf, "\"", 16), "\"\"\"\"");
	str_check(qident(buf, "a\"b", 16), "\"a\"\"b\"");
	str_check(qident(buf, "WHERE", 16), "\"WHERE\"");
	str_check(qident(buf, "where", 16), "\"where\"");
	str_check(qident(buf, "here", 16), "here");
	str_check(qident(buf, "in", 16), "\"in\"");

	str_check(qident(buf, "", 3), "\"\"");
	str_check(qident(buf, "", 2), "FAIL");
	str_check(qident(buf, "", 1), "FAIL");
	str_check(qident(buf, "", 0), "FAIL");

	str_check(qident(buf, "i", 2), "i");
	str_check(qident(buf, "i", 1), "FAIL");
	str_check(qident(buf, "i", 0), "FAIL");

	str_check(qident(buf, "a\"b", 7), "\"a\"\"b\"");
	str_check(qident(buf, "a\"b", 6), "FAIL");
	str_check(qident(buf, "a\"b", 5), "FAIL");
	str_check(qident(buf, "a\"b", 4), "FAIL");
	str_check(qident(buf, "a\"b", 3), "FAIL");
end:;
}

/*
 * quote_fqident
 */

static char *fqident(char *dst, const char *src, int size)
{
	if (pg_quote_fqident(dst, src, size))
		return dst;
	return "FAIL";
}

static void test_quote_fqident(void *ptr)
{
	char buf[128];
	str_check(fqident(buf, "", 16), "public.\"\"");
	str_check(fqident(buf, "baz.foo", 16), "baz.foo");
	str_check(fqident(buf, "baz.foo.bar", 16), "baz.\"foo.bar\"");
	str_check(fqident(buf, "where.in", 16), "\"where\".\"in\"");

	str_check(fqident(buf, "a.b", 4), "a.b");
	str_check(fqident(buf, "a.b", 3), "FAIL");
	str_check(fqident(buf, "a.b", 1), "FAIL");
	str_check(fqident(buf, "a.b", 0), "FAIL");

	str_check(fqident(buf, "i", 9), "public.i");
	str_check(fqident(buf, "i", 8), "FAIL");
end:;
}

/*
 * Describe
 */

struct testcase_t pgutil_tests[] = {
	{ "pg_quote_literal", test_quote_lit },
	{ "pg_quote_ident", test_quote_ident },
	{ "pg_quote_fqident", test_quote_fqident },
	END_OF_TESTCASES
};

