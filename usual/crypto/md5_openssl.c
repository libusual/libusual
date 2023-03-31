/*
 * Using MD5 OPENSSL APIs.
 */
#include <usual/crypto/md5.h>
#include <usual/crypto/digest.h>

#ifdef OPENSSL_API_COMPAT
static void md5_crypt_cleanup(struct md5_ctx *ctx)
{
	log_error("MD5 authentication: %s",ERR_reason_error_string(ERR_get_error()));
	EVP_MD_CTX_destroy(ctx->evpctx);
	ctx->evpctx = NULL;
	ERR_clear_error();
}

static void  md5_init(struct md5_ctx *ctx)
{
	if (ctx->evpctx != NULL &&
		EVP_DigestInit_ex(ctx->evpctx, EVP_md5(), NULL) <= 0)
	{
		md5_crypt_cleanup(ctx);
	}
}
void md5_reset(struct md5_ctx *ctx)
{
	ERR_clear_error();
	ctx->evpctx = EVP_MD_CTX_create();

	if (ctx->evpctx == NULL)
		log_error("MD5 authentication: out of memory");

	md5_init(ctx);
}

void md5_update(struct md5_ctx *ctx, const void *data, unsigned int len)
{
	if (ctx->evpctx != NULL &&
		EVP_DigestUpdate(ctx->evpctx, data, len) <= 0)
	{
		md5_crypt_cleanup(ctx);
	}
}

void md5_final(struct md5_ctx *ctx, uint8_t *dst)
{
	if (ctx->evpctx != NULL &&
		EVP_DigestFinal_ex(ctx->evpctx, dst, 0) <= 0)
	{
		md5_crypt_cleanup(ctx);
	}
	else
	{
		EVP_MD_CTX_destroy(ctx->evpctx);
	}
}

/*
 * DigestInfo
 */

static const struct DigestInfo md5 = {
	(DigestInitFunc *)md5_reset,
	(DigestUpdateFunc *)md5_update,
	(DigestFinalFunc *)md5_final,
	sizeof(struct md5_ctx),
	MD5_DIGEST_LENGTH,
	MD5_BLOCK_LENGTH
};

const struct DigestInfo *digest_MD5(void)
{
	return &md5;
}
#endif
