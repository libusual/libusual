

#include "test_common.h"

#include <locale.h>

#include <usual/time.h>
#include <usual/psrandom.h>

unsigned long long test_seed1, test_seed2;

struct testgroup_t groups[] = {
	{ "aatree/", aatree_tests },
	{ "base/", base_tests },
	{ "bits/", bits_tests },
	{ "cbtree/", cbtree_tests },
	{ "cfparser/", cfparser_tests },
	{ "crypto/", crypto_tests },
	{ "ctype/", ctype_tests },
	{ "cxalloc/", cxalloc_tests },
	{ "endian/", endian_tests },
	{ "event/", event_tests },
	{ "fileutil/", fileutil_tests },
	{ "fnmatch/", fnmatch_tests },
	{ "getopt/", getopt_tests },
	{ "hashing/", hashing_tests },
	{ "hashtab/", hashtab_tests },
	{ "heap/", heap_tests },
	{ "json/", json_tests },
	{ "list/", list_tests },
	{ "mdict/", mdict_tests },
	{ "netdb/", netdb_tests },
	{ "pgutil/", pgutil_tests },
	{ "psrandom/", psrandom_tests },
	{ "regex/", regex_tests },
	{ "shlist/", shlist_tests },
	{ "socket/", socket_tests },
	{ "string/", string_tests },
	{ "strpool/", strpool_tests },
	{ "talloc/", talloc_tests },
	{ "time/", time_tests },
	{ "tls/", tls_tests },
	{ "utf8/", utf8_tests },
	{ "wchar/", wchar_tests },
	END_OF_GROUPS
};

int main(int argc, const char *argv[])
{
	if (getenv("USE_LOCALE"))
		setlocale(LC_ALL, "");

	test_seed1 = pseudo_random();
	test_seed2 = pseudo_random();
	pseudo_random_seed(test_seed1, test_seed2);
	printf("inital seed: %llu %llu\n", test_seed1, test_seed2);

	return tinytest_main(argc, argv, groups);
}

