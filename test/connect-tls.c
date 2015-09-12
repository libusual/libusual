
#include <usual/tls/tls.h>
#include <usual/tls/tls_cert.h>
#include <usual/err.h>
#include <usual/time.h>

#ifdef USUAL_LIBSSL_FOR_TLS
#include <openssl/crypto.h>
#endif

static void show_time(const char *desc, time_t t)
{
	const char *val;
	val = t ? ctime(&t) : "--\n";
	printf("%s: %s", desc, val);
}

static void show_ocsp_info(struct tls *ctx)
{
	struct tls_ocsp_info *info;
	info = tls_get_ocsp_info(ctx);
	if (info) {
		printf("  status=%d reason=%d\n", info->status, info->reason);
		show_time("  this update", info->this_update);
		show_time("  next update", info->next_update);
		show_time("  revocation", info->revocation_time);
		tls_ocsp_info_free(info);
	}
}
int main(int argc, char *argv[])
{
	struct tls_config *conf;
	struct tls *ctx, *ocsp;
	struct tls_cert *cert;
	int res;
	const char *host;
	char buf[256];

	if (argc < 2)
		errx(1, "give host as arg\n");
	host = argv[1];

#ifdef USUAL_LIBSSL_FOR_TLS
	printf("libssl: %s\n", SSLeay_version(SSLEAY_VERSION));
#endif
	res = tls_init();
	if (res < 0)
		errx(1, "tls_init");

	conf = tls_config_new();
	if (!conf)
		errx(1, "tls_config_new");

	tls_config_set_protocols(conf, TLS_PROTOCOLS_ALL);
	tls_config_set_ciphers(conf, "fast");

	ctx = tls_client();
	if (!ctx)
		errx(1, "tls_client");

	res = tls_configure(ctx, conf);
	if (res < 0)
		errx(1, "tls_configure: %s", tls_error(ctx));

	res = tls_connect(ctx, host, "443");
	if (res < 0)
		errx(1, "tls_connect: %s", tls_error(ctx));

	res = tls_handshake(ctx);
	if (res < 0)
		errx(1, "tls_handshake: %s", tls_error(ctx));

	res = tls_get_peer_cert(ctx, &cert, NULL);
	if (res < 0)
		errx(1, "tls_get_peer_cert: %s", tls_error(ctx));

	tls_get_connection_info(ctx, buf, sizeof buf);

	printf("Connection: '%s'\n", buf);
	printf("  CN='%s'\n", cert->subject.common_name);
	printf("  C='%s'\n", cert->subject.country_name);
	printf("  ST='%s'\n", cert->subject.state_or_province_name);
	printf("  L='%s'\n", cert->subject.locality_name);
	printf("  S='%s'\n", cert->subject.street_address);
	printf("  O='%s'\n", cert->subject.organization_name);
	printf("  OU='%s'\n", cert->subject.organizational_unit_name);

	printf("OCSP stapling:\n");
	show_ocsp_info(ctx);

	ocsp = NULL;
	res = tls_ocsp_check_peer(&ocsp, NULL, ctx);
	tls_get_connection_info(ocsp, buf, sizeof buf);
	printf("OCSP responder: '%s'\n", buf);
	show_ocsp_info(ocsp);
	tls_free(ocsp);

	tls_close(ctx);
	tls_free(ctx);
	tls_config_free(conf);
	tls_cert_free(cert);

	return 0;
}

