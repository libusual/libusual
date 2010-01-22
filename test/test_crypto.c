
#include <usual/string.h>

#include "tinytest.h"
#include "tinytest_macros.h"

#define str_check(a, b) tt_str_op(a, ==, b)

#include <usual/md5.h>
#include <usual/sha1.h>

static const char *mkhex(const uint8_t *src, int len)
{
	static char buf[128];
	static const char hextbl[] = "0123456789abcdef";
	int i;
	for (i = 0; i < len; i++) {
		buf[i*2] = hextbl[src[i] >> 4];
		buf[i*2+1] = hextbl[src[i] & 15];
	}
	buf[i*2] = 0;
	return buf;
}

/*
 * MD5
 */

static const char *run_md5(const char *str)
{
	struct md5_ctx ctx[1];
	uint8_t res[MD5_DIGEST_LENGTH];
	uint8_t res2[MD5_DIGEST_LENGTH];
	int i, len = strlen(str), step;

	md5_reset(ctx);
	md5_update(ctx, str, len);
	md5_final(res, ctx);

	md5_reset(ctx);
	step = 3;
	for (i = 0; i < len; i += step)
		md5_update(ctx, str+i,
			   (i + step <= len)
			   ? (step) : (len - i));
	md5_final(res2, ctx);

	if (memcmp(res, res2, MD5_DIGEST_LENGTH) != 0)
		return "FAIL";
	
	return mkhex(res, MD5_DIGEST_LENGTH);
}

static void test_md5(void *ptr)
{
	str_check(run_md5(""), "d41d8cd98f00b204e9800998ecf8427e");
	str_check(run_md5("a"), "0cc175b9c0f1b6a831c399e269772661");
	str_check(run_md5("abc"), "900150983cd24fb0d6963f7d28e17f72");
	str_check(run_md5("message digest"), "f96b697d7cb7938d525a2f31aaf161d0");
	str_check(run_md5("abcdefghijklmnopqrstuvwxyz"), "c3fcd3d76192e4007dfb496cca67e13b");
	str_check(run_md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "d174ab98d277d9f5a5611c2c9f419d9f");
	str_check(run_md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "57edf4a22be3c955ac49da2e2107b67a");
end:;
}

/*
 * SHA1
 */

static const char *run_sha1(const char *str)
{
	struct sha1_ctx ctx[1];
	uint8_t res[SHA1_DIGEST_LENGTH];
	uint8_t res2[SHA1_DIGEST_LENGTH];
	int i, len = strlen(str), step;

	sha1_reset(ctx);
	sha1_update(ctx, str, len);
	sha1_final(res, ctx);

	sha1_reset(ctx);
	step = 3;
	for (i = 0; i < len; i += step)
		sha1_update(ctx, str+i,
			    (i + step <= len)
			    ? (step) : (len - i));
	sha1_final(res2, ctx);

	if (memcmp(res, res2, SHA1_DIGEST_LENGTH) != 0)
		return "FAIL";
	
	return mkhex(res, SHA1_DIGEST_LENGTH);
}

static void test_sha1(void *ptr)
{
	str_check(run_sha1(""), "da39a3ee5e6b4b0d3255bfef95601890afd80709");
	str_check(run_sha1("a"), "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8");
	str_check(run_sha1("abc"), "a9993e364706816aba3e25717850c26c9cd0d89d");
	str_check(run_sha1("message digest"), "c12252ceda8be8994d5fa0290a47231c1d16aae3");
	str_check(run_sha1("abcdefghijklmnopqrstuvwxyz"), "32d10c7b8cf96570ca04ce37f2a19d84240d3a89");
	str_check(run_sha1("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "761c457bf73b14d27e9e9265c46f4b4dda11f940");
	str_check(run_sha1("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "50abf5706a150990a08b2c5ea40fa0e585554732");
end:;
}

/*
 * Laucher.
 */

struct testcase_t crypto_tests[] = {
	{ "md5", test_md5 },
	{ "sha1", test_sha1 },
	END_OF_TESTCASES
};

