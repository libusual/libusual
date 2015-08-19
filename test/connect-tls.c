
#include <usual/tls/tls.h>
#include <usual/err.h>

int main(int argc, char *argv[])
{
	struct tls_config *conf;
	struct tls *ctx;
	struct tls_cert_info *cert;
	int res;
	const char *host;

	if (argc < 2)
		errx(1, "give host as arg\n");
	host = argv[1];

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

	printf("connect ok\n");

	res = tls_get_peer_cert(ctx, &cert);
	if (res < 0)
		errx(1, "tls_get_peer_cert: %s", tls_error(ctx));

	tls_close(ctx);
	tls_free(ctx);
	tls_config_free(conf);

	printf("  CN='%s'\n", cert->subject.common_name);
	printf("  C='%s'\n", cert->subject.country_name);
	printf("  ST='%s'\n", cert->subject.state_or_province_name);
	printf("  L='%s'\n", cert->subject.locality_name);
	printf("  S='%s'\n", cert->subject.street_address);
	printf("  O='%s'\n", cert->subject.organization_name);
	printf("  OU='%s'\n", cert->subject.organizational_unit_name);

	tls_cert_free(cert);
	return 0;
}

