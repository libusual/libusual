
#include <usual/netdb.h>

#include <usual/string.h>

#include "test_common.h"


static void test_gai(void *p)
{
	int res;
	struct sigevent sev;

	memset(&sev, 0, sizeof(sev));

	sev.sigev_notify = SIGEV_THREAD;

	res = getaddrinfo_a(GAI_NOWAIT, NULL, 0, &sev);

	int_check(res, 0);
end:;
}

struct testcase_t netdb_tests[] = {
	{ "getaddrinfo_a", test_gai },
	END_OF_TESTCASES
};

