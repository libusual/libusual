/* $OpenBSD: by_mem.c,v 1.2 2015/01/22 11:16:56 jsing Exp $ */
/* $OpenBSD: ssl_rsa.c,v 1.19 2014/12/14 15:30:50 jsing Exp $ */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

/*
 * LibreSSL compat for other OpenSSL's.
 */

#include "tls_compat.h"

#ifdef USUAL_LIBSSL_FOR_TLS

#include <openssl/err.h>

#ifndef HAVE_SSL_CTX_USE_CERTIFICATE_CHAIN_MEM

/*
 * Read a bio that contains our certificate in "PEM" format,
 * possibly followed by a sequence of CA certificates that should be
 * sent to the peer in the Certificate message.
 */
static int
ssl_ctx_use_certificate_chain_bio(SSL_CTX *ctx, BIO *in)
{
	int ret = 0;
	X509 *x = NULL;

	ERR_clear_error(); /* clear error stack for SSL_CTX_use_certificate() */

	x = PEM_read_bio_X509_AUX(in, NULL, ctx->default_passwd_callback,
	    ctx->default_passwd_callback_userdata);
	if (x == NULL) {
		SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_CHAIN_FILE, ERR_R_PEM_LIB);
		goto end;
	}

	ret = SSL_CTX_use_certificate(ctx, x);

	if (ERR_peek_error() != 0)
		ret = 0;
	/* Key/certificate mismatch doesn't imply ret==0 ... */
	if (ret) {
		/*
		 * If we could set up our certificate, now proceed to
		 * the CA certificates.
		 */
		X509 *ca;
		int r;
		unsigned long err;

		if (ctx->extra_certs != NULL) {
			sk_X509_pop_free(ctx->extra_certs, X509_free);
			ctx->extra_certs = NULL;
		}

		while ((ca = PEM_read_bio_X509(in, NULL,
		    ctx->default_passwd_callback,
		    ctx->default_passwd_callback_userdata)) != NULL) {
			r = SSL_CTX_add_extra_chain_cert(ctx, ca);
			if (!r) {
				X509_free(ca);
				ret = 0;
				goto end;
			}
			/*
			 * Note that we must not free r if it was successfully
			 * added to the chain (while we must free the main
			 * certificate, since its reference count is increased
			 * by SSL_CTX_use_certificate).
			 */
		}

		/* When the while loop ends, it's usually just EOF. */
		err = ERR_peek_last_error();
		if (ERR_GET_LIB(err) == ERR_LIB_PEM &&
		    ERR_GET_REASON(err) == PEM_R_NO_START_LINE)
			ERR_clear_error();
		else
			ret = 0; /* some real error */
	}

end:
	if (x != NULL)
		X509_free(x);
	return (ret);
}

int
SSL_CTX_use_certificate_chain_mem(SSL_CTX *ctx, void *buf, int len)
{
	BIO *in;
	int ret = 0;

	in = BIO_new_mem_buf(buf, len);
	if (in == NULL) {
		SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_CHAIN_FILE, ERR_R_BUF_LIB);
		goto end;
	}

	ret = ssl_ctx_use_certificate_chain_bio(ctx, in);

end:
	BIO_free(in);
	return (ret);
}

#endif

#ifndef HAVE_SSL_CTX_LOAD_VERIFY_MEM

/*
 * Load CA certs from memory.
 */

int SSL_CTX_load_verify_mem(SSL_CTX *ctx, void *data, int data_len)
{
	STACK_OF(X509_INFO)	*inf = NULL;
	X509_INFO		*itmp;
	BIO			*in = NULL;
	int			 i, count = 0, ok = 0;

	if ((in = BIO_new_mem_buf(data, data_len)) == NULL)
		goto done;

	if ((inf = PEM_X509_INFO_read_bio(in, NULL, NULL, NULL)) == NULL)
		goto done;

	for (i = 0; i < sk_X509_INFO_num(inf); i++) {
		itmp = sk_X509_INFO_value(inf, i);
		if (itmp->x509) {
			ok = X509_STORE_add_cert(ctx->cert_store, itmp->x509);
			if (!ok)
				goto done;
			count++;
		}
		if (itmp->crl) {
			ok = X509_STORE_add_crl(ctx->cert_store, itmp->crl);
			if (!ok)
				goto done;
			count++;
		}
	}

	ok = count != 0;
 done:
	if (count == 0)
		X509err(X509_F_X509_LOAD_CERT_CRL_FILE,ERR_R_PEM_LIB);
	if (inf != NULL)
		sk_X509_INFO_pop_free(inf, X509_INFO_free);
	if (in != NULL)
		BIO_free(in);
	return (ok);
}

#endif

#endif /* !USUAL_LIBSSL_FOR_TLS */
