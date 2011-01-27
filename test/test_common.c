

#include "test_common.h"

struct testgroup_t groups[] = {
	{ "base/", base_tests },
	{ "aatree/", aatree_tests },
	{ "bits/", bits_tests },
	{ "cxalloc/", cxalloc_tests },
	{ "cbtree/", cbtree_tests },
	{ "crypto/", crypto_tests },
	{ "endian/", endian_tests },
	{ "string/", string_tests },
	{ "heap/", heap_tests },
	{ "hashtab/", hashtab_tests },
	{ "list/", list_tests },
	{ "utf8/", utf8_tests },
	{ "strpool/", strpool_tests },
	{ "pgutil/", pgutil_tests },
	{ "regex/", regex_tests },
	{ "netdb/", netdb_tests },
	{ "cfparser/", cfparser_tests },
	END_OF_GROUPS
};

int main(int argc, const char *argv[])
{
	return tinytest_main(argc, argv, groups);
}

