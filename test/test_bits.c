
#include <usual/bits.h>

#include "test_common.h"

/*
 * is_power_of_2
 */

static void test_pow2(void *p)
{
	int_check(is_power_of_2(0), 0);
	int_check(is_power_of_2(1), 1);
	int_check(is_power_of_2(2), 1);
	int_check(is_power_of_2(3), 0);
end:;
}

/*
 * rol
 */

static void test_rol(void *p)
{
	/* rol16 */
	int_check(rol16(1, 1), 2);
	int_check(rol16(1, 15), 32768);
	int_check(rol16(0x8000, 1), 1);

	/* rol32 */
	int_check(rol32(1, 1), 2);
	int_check(rol32(0x80000000, 1), 1);

	/* rol64 */
	ull_check(rol64(1, 1), 2);
	ull_check(rol64(1, 63), 0x8000000000000000);
end:;
}

/*
 * ror
 */

static void test_ror(void *p)
{
	/* ror16 */
	int_check(ror16(1, 1), 0x8000);
	/* ror32 */
	int_check(ror32(1, 1), 0x80000000);
	/* ror64 */
	ull_check(ror64(1, 1), 0x8000000000000000ULL);
end:;
}

/*
 * fls
 */

static void test_fls(void *p)
{
	/* fls */
	int_check(fls(0), 0);
	int_check(fls(1), 1);
	int_check(fls(3), 2);
	int_check(fls((int)-1), 32);

	/* flsl */
	int_check(flsl(0), 0);
	int_check(flsl(1), 1);
	int_check(flsl(3), 2);
	if (sizeof(long) == 4)
		int_check(flsl((long)-1), 32);
	else
		int_check(flsl((long)-1), 64);

	/* flsll */
	int_check(flsll(0), 0);
	int_check(flsll(1), 1);
	int_check(flsll(3), 2);
	int_check(flsll((long long)-1), 64);
end:;
}

/*
 * ffs
 */

static void test_ffs(void *p)
{
	/* ffs */
	int_check(ffs(0), 0);
	int_check(ffs(1), 1);
	int_check(ffs(3), 1);
	int_check(ffs((int)-1), 1);
	int_check(ffs(ror32(1,1)), 32);

	/* flsl */
	int_check(ffsl(0), 0);
	int_check(ffsl(1), 1);
	int_check(ffsl(3), 1);
	int_check(ffsl((long)-1), 1);
	if (sizeof(long) == 4)
		int_check(ffsl(ror32(1,1)), 32);
	else
		int_check(ffsl(ror64(1,1)), 64);

	/* ffsll */
	int_check(ffsll(0), 0);
	int_check(ffsll(1), 1);
	int_check(ffsll(3), 1);
	int_check(ffsll((long long)-1), 1);
	ull_check((1ULL << 63), ror64(1,1));
	int_check(ffsll(1ULL << 63), 64);
	int_check(ffsll(ror64(1,1)), 64);
end:;
}


/*
 * Describe
 */

struct testcase_t bits_tests[] = {
	{ "is_power_of_2", test_pow2 },
	{ "rol", test_rol },
	{ "ror", test_ror },
	{ "ffs", test_ffs },
	{ "fls", test_fls },
	END_OF_TESTCASES
};

