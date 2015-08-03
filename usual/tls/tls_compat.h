
#ifndef _USUAL_TLS_COMPAT_H_
#define _USUAL_TLS_COMPAT_H_

#include <usual/tls/tls.h>

#ifdef USUAL_LIBSSL_FOR_TLS

#include <usual/crypto/csrandom.h>
#include <usual/string.h>
#include <usual/socket.h>

#include <openssl/ssl.h>

#ifndef HAVE_ARC4RANDOM_BUF
#define arc4random_buf(a,b) csrandom_bytes(a,b)
#endif

#ifndef SSL_CTX_set_dh_auto
long SSL_CTX_set_dh_auto(SSL_CTX *ctx, int onoff);
#endif

#ifndef SSL_CTX_set_ecdh_auto
long SSL_CTX_set_ecdh_auto(SSL_CTX *ctx, int onoff);
#endif

#ifndef HAVE_SSL_CTX_USE_CERTIFICATE_CHAIN_MEM
int SSL_CTX_use_certificate_chain_mem(SSL_CTX *ctx, void *buf, int len);
#endif

#ifndef HAVE_SSL_CTX_LOAD_VERIFY_MEM
int SSL_CTX_load_verify_mem(SSL_CTX *ctx, void *buf, int len);
#endif

#endif /* USUAL_LIBSSL_FOR_TLS */

#endif /* _USUAL_TLS_COMPAT_H_ */

