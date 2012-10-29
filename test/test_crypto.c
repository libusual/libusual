
#include <usual/string.h>

#include "tinytest.h"
#include "tinytest_macros.h"

#define str_check(a, b) tt_str_op(a, ==, b)

#include <usual/crypto/hmac.h>
#include <usual/crypto/md5.h>
#include <usual/crypto/sha1.h>
#include <usual/crypto/sha256.h>
#include <usual/crypto/sha512.h>
#include <usual/crypto/digest.h>
#include <usual/cxalloc.h>

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

static const char *run_hash(const char *str, const struct DigestInfo *impl)
{
	struct DigestContext *ctx;
	uint8_t res[512];
	uint8_t res2[512];
	int i, len = strlen(str), step;
	int reslen;

	ctx = digest_new(impl, USUAL_ALLOC);
	if (!ctx)
		return "NOMEM";
	reslen = digest_result_len(ctx);

	digest_update(ctx, str, len);
	digest_final(ctx, res);

	digest_reset(ctx);
	step = 3;
	for (i = 0; i < len; i += step)
		digest_update(ctx, str+i,
			      (i + step <= len) ? (step) : (len - i));
	digest_final(ctx, res2);

	digest_free(ctx);

	if (memcmp(res, res2, reslen) != 0)
		return "FAIL";
	
	return mkhex(res, reslen);
}

/*
 * MD5
 */

static const char *run_md5(const char *str)
{
	return run_hash(str, digest_MD5());
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
	return run_hash(str, digest_SHA1());
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
 * SHA224
 */

static const char *run_sha224(const char *str)
{
	return run_hash(str, digest_SHA224());
}

static void test_sha224(void *ptr)
{
	str_check(run_sha224(""), "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f");
	str_check(run_sha224("a"), "abd37534c7d9a2efb9465de931cd7055ffdb8879563ae98078d6d6d5");
	str_check(run_sha224("abc"), "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7");
	str_check(run_sha224("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"), "75388b16512776cc5dba5da1fd890150b0c6455cb4f58b1952522525");
	str_check(run_sha224("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "b50aecbe4e9bb0b57bc5f3ae760a8e01db24f203fb3cdcd13148046e");
end:;
}

/*
 * SHA256
 */

static const char *run_sha256(const char *str)
{
	return run_hash(str, digest_SHA256());
}

static void test_sha256(void *ptr)
{
	str_check(run_sha256(""), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	str_check(run_sha256("a"), "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
	str_check(run_sha256("abc"), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	str_check(run_sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
	str_check(run_sha256("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "f371bc4a311f2b009eef952dd83ca80e2b60026c8e935592d0f9c308453c813e");
end:;
}

/*
 * SHA384
 */

static const char *run_sha384(const char *str)
{
	return run_hash(str, digest_SHA384());
}

static void test_sha384(void *ptr)
{
	str_check(run_sha384(""), "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b");
	str_check(run_sha384("a"), "54a59b9f22b0b80880d8427e548b7c23abd873486e1f035dce9cd697e85175033caa88e6d57bc35efae0b5afd3145f31");
	str_check(run_sha384("abc"), "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7");
	str_check(run_sha384("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
		  "3391fdddfc8dc7393707a65b1b4709397cf8b1d162af05abfe8f450de5f36bc6b0455a8520bc4e6f5fe95b1fe3c8452b");
	str_check(run_sha384("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"),
		  "09330c33f71147e83d192fc782cd1b4753111b173b3b05d22fa08086e3b0f712fcc7c71a557e2db966c3e9fa91746039");
	str_check(run_sha384("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"),
		  "3d208973ab3508dbbd7e2c2862ba290ad3010e4978c198dc4d8fd014e582823a89e16f9b2a7bbc1ac938e2d199e8bea4");
end:;
}

/*
 * SHA512
 */

static const char *run_sha512(const char *str)
{
	return run_hash(str, digest_SHA512());
}

static void test_sha512(void *ptr)
{
	str_check(run_sha512(""), "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
	str_check(run_sha512("a"), "1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75");
	str_check(run_sha512("abc"), "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
	str_check(run_sha512("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
		  "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c33596fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445");
	str_check(run_sha512("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"),
		  "930d0cefcb30ff1133b6898121f1cf3d27578afcafe8677c5257cf069911f75d8f5831b56ebfda67b278e66dff8b84fe2b2870f742a580d8edb41987232850c9");
	str_check(run_sha512("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"),
		  "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909");
end:;
}


/*
 * HMAC
 */

static const char *run_hmac(const char *key, const char *str, const struct DigestInfo *impl)
{
	struct HMAC *ctx;
	uint8_t res[512];
	int len = strlen(str);
	int reslen;

	ctx = hmac_new(impl, key, strlen(key), USUAL_ALLOC);
	if (!ctx)
		return "NOMEM";
	reslen = hmac_result_len(ctx);

	hmac_update(ctx, str, len);
	hmac_final(ctx, res);

	return mkhex(res, reslen);
}

static const char *run_hmac_sha1(const char *key, const char *str)
{
	return run_hmac(key, str, digest_SHA1());
}

static void test_hmac(void *ptr)
{
	const char *long_key = (
		"quite a very long key, longer than a sha1 block size, "
		"so it needs to be sha-1d before being used as a key");
	const char *text = "The quick brown fox jumps over the lazy dog";

	str_check(run_hmac_sha1("", ""),
			  "fbdb1d1b18aa6c08324b7d64b71fb76370690e1d");

	str_check(run_hmac_sha1("shrt", ""),
			  "41fee95de96c437cf6c2f38363eb38eb0067ff64");

	str_check(run_hmac_sha1(long_key, ""),
		"496ca9bda3e523814ba7f99f68a2035e4de7702a");

	str_check(run_hmac_sha1(long_key, text),
		"924e1ee84da31f5f569a27dd6201533b42c999c6");

	str_check(run_hmac_sha1("key", text),
		"de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9");
end:;
}

/*
 * Launcher.
 */

struct testcase_t crypto_tests[] = {
	{ "md5", test_md5 },
	{ "sha1", test_sha1 },
	{ "sha224", test_sha224 },
	{ "sha256", test_sha256 },
	{ "sha384", test_sha384 },
	{ "sha512", test_sha512 },
	{ "hmac", test_hmac },
	END_OF_TESTCASES
};

