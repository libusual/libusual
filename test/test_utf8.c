
#include <usual/utf8.h>

#include "test_common.h"

#include <stdarg.h>

static int uget1(int a)
{
	char buf[2] = { a, 0 };
	const char *p = buf;
	return utf8_get_char(&p, buf + 1);
}

static int uget2(int a, int b)
{
	char buf[3] = { a, b, 0 };
	const char *p = buf;
	return utf8_get_char(&p, buf + 2);
}

static int uget3(int a, int b, int c)
{
	char buf[4] = { a, b, c, 0 };
	const char *p = buf;
	return utf8_get_char(&p, buf + 3);
}

static int uget4(int a, int b, int c, int d)
{
	char buf[5] = { a, b, c, d, 0 };
	const char *p = buf;
	return utf8_get_char(&p, buf + 4);
}


static void test_utf8_char_size(void *p)
{
	int_check(utf8_char_size(0), 1);
	int_check(utf8_char_size('a'), 1);
	int_check(utf8_char_size(0x7F), 1);
	int_check(utf8_char_size(0x80), 2);
	int_check(utf8_char_size(0x7FF), 2);
	int_check(utf8_char_size(0x800), 3);
	int_check(utf8_char_size(0xFFFF), 3);
	int_check(utf8_char_size(0x10000), 4);
	int_check(utf8_char_size(0x100000), 4);
	int_check(utf8_char_size(0x10FFFF), 4);
end:;
}

static void test_utf8_seq_size(void *p)
{
	int_check(utf8_seq_size(0), 1);
	int_check(utf8_seq_size(0x7F), 1);
	int_check(utf8_seq_size(0x80), 0);
	int_check(utf8_seq_size(0xBF), 0);
	int_check(utf8_seq_size(0xC0), 0);
	int_check(utf8_seq_size(0xC1), 0);
	int_check(utf8_seq_size(0xC2), 2);
	int_check(utf8_seq_size(0xDF), 2);
	int_check(utf8_seq_size(0xE0), 3);
	int_check(utf8_seq_size(0xEF), 3);
	int_check(utf8_seq_size(0xF0), 4);
	int_check(utf8_seq_size(0xF4), 4);
	int_check(utf8_seq_size(0xF5), 0);
	int_check(utf8_seq_size(0xFF), 0);
end:;
}

static void test_utf8_get_char(void *p)
{
	int_check(uget1(0), 0);
	int_check(uget1(0x7F), 0x7F);
	int_check(uget2(0xC2, 0xA2), 0xA2);
	int_check(uget2(0xC2, 0xA2), 0xA2);
	int_check(uget3(0xE2, 0x82, 0xAC), 0x20AC);
	int_check(uget4(0xF0, 0xA4, 0xAD, 0xA2), 0x024B62);

	/* invalid reads */
	int_check(uget1(0x80), -0x80);
	int_check(uget1(0xC1), -0xC1);
	int_check(uget3(0xE0, 0x82, 0xAC), -0xE0);

	/* short reads */
	int_check(uget1(0xC2), -0xC2);
	int_check(uget2(0xE2, 0x82), -0xE2);
	int_check(uget3(0xF0, 0xA4, 0xAD), -0xF0);
end:;
}

static void test_utf8_put_char(void *p)
{
	int_check(uget1(0), 0);
end:;
}

/*
 * Describe
 */

struct testcase_t utf8_tests[] = {
	{ "utf8_char_size", test_utf8_char_size },
	{ "utf8_seq_size", test_utf8_seq_size },
	{ "utf8_get_char", test_utf8_get_char },
	{ "utf8_put_char", test_utf8_put_char },
	END_OF_TESTCASES
};

