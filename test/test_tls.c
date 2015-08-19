#include <usual/tls/tls.h>
#include <usual/event.h>
#include <usual/socket.h>
#include <usual/string.h>
#include <usual/signal.h>
#include <usual/err.h>
#include <usual/fileutil.h>
#include <usual/ctype.h>

#include <string.h>
#include <stdarg.h>

#include "test_common.h"

#ifdef USUAL_LIBSSL_FOR_TLS
#include <usual/tls/tls_internal.h>
#endif

enum WState {
	HANDSHAKE,
	CONNECTED,
	CLOSED
};

struct UseCase;
struct Worker;

struct Worker {
	struct event ev;
	struct event_base *evbase;
	struct tls *ctx;
	struct tls *base;
	struct tls_config *config;
	const char *hostname;
	bool is_server;
	bool pending;
	enum WState wstate;
	int socket;
	char errbuf[1024];

	const char *show;
	char showbuf[1024];

	const char *peer_fingerprint_sha1;
	const char *peer_fingerprint_sha256;
};

static void free_worker(struct Worker *w)
{
	if (!w)
		return;
	event_del(&w->ev);
	tls_config_free(w->config);
	tls_free(w->ctx);
	tls_free(w->base);
	memset(w, 0, sizeof *w);
	free(w);
}

static const char *add_error(struct Worker *w, const char *s)
{
	if (!s)
		return s;
	if (strcmp(s, "OK") == 0)
		return s;
	if (strstr(s, "SSL routines")) {
		s = strrchr(s, ':') + 1;
	}
	if (w->is_server) {
		if (w->errbuf[0]) {
			strlcat(w->errbuf, ",S:", sizeof w->errbuf);
		} else {
			strlcat(w->errbuf, "S:", sizeof w->errbuf);
		}
		strlcat(w->errbuf, s, sizeof w->errbuf);
	} else {
		if (w->errbuf[0]) {
			strlcat(w->errbuf, ",C:", sizeof w->errbuf);
		} else {
			strlcat(w->errbuf, "C:", sizeof w->errbuf);
		}
		strlcat(w->errbuf, s, sizeof w->errbuf);
	}
	w->wstate = CLOSED;
	return s;
}

static const char *check_errors(struct Worker *client, struct Worker *server)
{
	static char buf[1024];

	if (!client->errbuf[0] && !server->errbuf[0]) {
		if (server->show) {
			strlcpy(buf, server->showbuf, sizeof buf);
			return buf;
		}
		return "OK";
	}

	buf[0] = 0;
	strlcat(buf, client->errbuf, sizeof buf);
	if (buf[0] && server->errbuf[0])
		strlcat(buf, " - ", sizeof buf);
	strlcat(buf, server->errbuf, sizeof buf);
	return buf;
}

static const char *create_worker(struct Worker **w_p, bool is_server, ...)
{
	va_list ap;
	const char *k, *v;
	int klen;
	struct Worker *w;
	int err;
	const char *mem = NULL;
	void *fdata;
	size_t flen;

	*w_p = NULL;

	w = calloc(1, sizeof *w);
	if (!w)
		return "calloc";
	w->wstate = HANDSHAKE;
	w->is_server = is_server;
	w->config = tls_config_new();
	if (!w->config)
		return "tls_config_new failed";

	if (is_server) {
		w->base = tls_server();
		if (!w->base)
			return "tls_server failed";
	} else {
		w->ctx = tls_client();
		if (!w->ctx)
			return "tls_client failed";
	}

	va_start(ap, is_server);
	while (1) {
		k = va_arg(ap, char *);
		if (!k)
			break;
		v = strchr(k, '=');
		if (!v)
			return k;
		v++;
		klen = v - k;
		err = 0;
		if (!strncmp(k, "mem=", klen)) {
			mem = v;
		} else if (!strncmp(k, "ca=", klen)) {
			if (mem) {
				fdata = load_file(v, &flen);
				if (!fdata) return strerror(errno);
				err = tls_config_set_ca_mem(w->config, fdata, flen);
				free(fdata);
			} else {
				err = tls_config_set_ca_file(w->config, v);
			}
		} else if (!strncmp(k, "cert=", klen)) {
			if (mem) {
				fdata = load_file(v, &flen);
				if (!fdata) return strerror(errno);
				err = tls_config_set_cert_mem(w->config, fdata, flen);
				free(fdata);
			} else {
				err = tls_config_set_cert_file(w->config, v);
			}
		} else if (!strncmp(k, "key=", klen)) {
			if (mem) {
				fdata = load_file(v, &flen);
				if (!fdata) return strerror(errno);
				err = tls_config_set_key_mem(w->config, fdata, flen);
				free(fdata);
			} else {
				err = tls_config_set_key_file(w->config, v);
			}
		} else if (!strncmp(k, "show=", klen)) {
			w->show = v;
		} else if (!strncmp(k, "ciphers=", klen)) {
			err = tls_config_set_ciphers(w->config, v);
		} else if (!strncmp(k, "host=", klen)) {
			w->hostname = v;
		} else if (!strncmp(k, "noverifycert=", klen)) {
			tls_config_insecure_noverifycert(w->config);
		} else if (!strncmp(k, "noverifyname=", klen)) {
			tls_config_insecure_noverifyname(w->config);
		} else if (!strncmp(k, "verify=", klen)) {
			tls_config_verify(w->config);
		} else if (!strncmp(k, "dheparams=", klen)) {
			err = tls_config_set_dheparams(w->config, v);
		} else if (!strncmp(k, "ecdhecurve=", klen)) {
			err = tls_config_set_ecdhecurve(w->config, v);
		} else if (!strncmp(k, "protocols=", klen)) {
			uint32_t protos;
			err = tls_config_parse_protocols(&protos, v);
			tls_config_set_protocols(w->config, TLS_PROTOCOLS_ALL);
		} else if (!strncmp(k, "peer-sha1=", klen)) {
			w->peer_fingerprint_sha1 = v;
		} else if (!strncmp(k, "peer-sha256=", klen)) {
			w->peer_fingerprint_sha256 = v;
		} else {
			return k;
		}
		if (err < 0) {
			return k;
		}
	}
	va_end(ap);

	if (is_server) {
		if (tls_configure(w->base, w->config) < 0)
			return tls_error(w->base);
	} else {
		if (tls_configure(w->ctx, w->config) < 0)
			return tls_error(w->ctx);
	}

	*w_p = w;
	return "OK";
}

static const char *do_handshake(struct Worker *w, int fd);
static const char *wait_for_event(struct Worker *w, short flag);

static void worker_cb(int fd, short flags, void *arg)
{
	struct Worker *w = arg;
	const char *err;
	char buf[128];
	int res;
	size_t outlen;

	w->pending = 0;

	if (w->wstate == HANDSHAKE) {
		err = do_handshake(w, fd);
		add_error(w, err);
	} else if (w->wstate == CONNECTED) {
		if (flags & EV_READ) {
			res = tls_read(w->ctx, buf, sizeof buf, &outlen);
			if (res == TLS_READ_AGAIN) {
				wait_for_event(w, EV_READ);
			} else if (res == TLS_WRITE_AGAIN) {
				wait_for_event(w, EV_WRITE);
			} else if (res == 0) {
				if (outlen > 0 && w->is_server) {
					tls_write(w->ctx, "END", 3, &outlen);
					w->wstate = CLOSED;
				} else if (outlen == 0) {
					w->wstate = CLOSED;
				} else {
					wait_for_event(w, EV_READ);
				}
			} else {
				add_error(w, "bad pkt");
			}
		} else {
			add_error(w, "EV_WRITE?");
		}
	}
	if (w->wstate == CLOSED && w->ctx) {
		res = tls_close(w->ctx);
		if (res == 0) {
			tls_free(w->ctx);
			w->ctx = NULL;
		} else if (res == TLS_READ_AGAIN) {
			wait_for_event(w, EV_READ);
		} else if (res == TLS_WRITE_AGAIN) {
			wait_for_event(w, EV_WRITE);
		} else {
			tls_free(w->ctx);
			w->ctx = NULL;
		}
	}
	if (!w->pending && w->ctx) {
		errx(1, "missed event setup: %s flags=%d state=%d", w->is_server ? "S":"C", flags, w->wstate);
	}
	return;
}

static const char *mkhex(const uint8_t *src, int len, char *dst)
{
	static const char hextbl[] = "0123456789abcdef";
	int i;
	for (i = 0; i < len; i++) {
		dst[i*2] = hextbl[src[i] >> 4];
		dst[i*2+1] = hextbl[src[i] & 15];
	}
	dst[i*2] = 0;
	return dst;
}

static const char *hexcmp(const char *fn, const void *buf, unsigned int len)
{
	char hexbuf[256];
	size_t flen;
	char *fdata = load_file(fn, &flen);
	int cmp;

	if (!fdata)
		return strerror(errno);
	while (flen && isspace(fdata[flen-1]))
		flen--;
	fdata[flen] = 0;

	mkhex(buf, len, hexbuf);

	cmp = strcmp(hexbuf, fdata);
	free(fdata);
	return cmp ? "Fingerprint does not match" : NULL;
}

static const char *check_fp(struct Worker *w, const char *algo, const char *fn, size_t xlen)
{
	char buf[128];
	const char *emsg;
	int res;
	size_t outlen = 0;

	if (!fn)
		return NULL;

	res = tls_get_peer_cert_fingerprint(w->ctx, algo, buf, sizeof buf, &outlen);
	if (res != 0 || outlen != xlen)
		return "FP-sha1-fail";
	emsg = hexcmp(fn, buf, outlen);
	if (emsg)
		return emsg;
	return NULL;
}

static void show_append(char *buf, size_t buflen, const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return;
	strlcat(buf, s1, buflen);
	strlcat(buf, s2, buflen);
}

static void show_entity(char *buf, size_t buflen, const struct tls_cert_entity *ent)
{
	show_append(buf, buflen, "/CN=", ent->common_name);
	show_append(buf, buflen, "/C=", ent->country_name);
	show_append(buf, buflen, "/ST=", ent->state_or_province_name);
	show_append(buf, buflen, "/L=", ent->locality_name);
	show_append(buf, buflen, "/O=", ent->organization_name);
	show_append(buf, buflen, "/OU=", ent->organizational_unit_name);
	show_append(buf, buflen, "/E=", ent->email_address);
}

static void show_cert(struct tls_cert_info *cert, char *buf, size_t buflen)
{
	if (!cert) {
		snprintf(buf, buflen, "no cert");
		return;
	}
	show_append(buf, buflen, "Subject: ", "");
	show_entity(buf, buflen, &cert->subject);
	show_append(buf, buflen, " Issuer: ", "");
	show_entity(buf, buflen, &cert->issuer);
	show_append(buf, buflen, " Serial: ", cert->serial);
	show_append(buf, buflen, " NotBefore: ", cert->not_before);
	show_append(buf, buflen, " NotAfter: ", cert->not_after);
}

static const char *done_handshake(struct Worker *w)
{
	int res;
	size_t outlen = 0;
	const char *emsg;

	emsg = check_fp(w, "sha1", w->peer_fingerprint_sha1, 20);
	if (emsg)
		return emsg;
	emsg = check_fp(w, "sha256", w->peer_fingerprint_sha256, 32);
	if (emsg)
		return emsg;

	if (w->show) {
		if (strcmp(w->show, "ciphers") == 0) {
			tls_get_connection_info(w->ctx, w->showbuf, sizeof w->showbuf);
		} else if (strcmp(w->show, "peer-cert") == 0) {
			struct tls_cert_info *cert = NULL;
			tls_get_peer_cert(w->ctx, &cert);
			show_cert(cert, w->showbuf, sizeof w->showbuf);
			tls_cert_free(cert);
		} else {
			snprintf(w->showbuf, sizeof w->showbuf, "bad kw: show=%s", w->show);
		}
	}

	if (!w->is_server) {
		res = tls_write(w->ctx, "PKT", 3, &outlen);
		if (res != 0 && outlen != 3)
			return "write!=3";
	}
	return wait_for_event(w, EV_READ);
}

static const char *wait_for_event(struct Worker *w, short flags)
{
	event_assign(&w->ev, w->evbase, w->socket, flags, worker_cb, w);
	tt_assert(event_add(&w->ev, NULL) == 0);
	w->pending = 1;
	return "OK";
end:
	return add_error(w, "event_add failed");
}

static const char *do_handshake(struct Worker *w, int fd)
{
	int err;
	const char *msg;
	if (w->is_server) {
		err = tls_accept_socket(w->base, &w->ctx, fd);
	} else {
		err = tls_connect_socket(w->ctx, fd, w->hostname);
	}
	if (err == TLS_READ_AGAIN) {
		return wait_for_event(w, EV_READ);
	} else if (err == TLS_WRITE_AGAIN) {
		return wait_for_event(w, EV_WRITE);
	} else if (err == 0) {
		w->wstate = CONNECTED;
		return done_handshake(w);
	}
	msg = tls_error(w->ctx ? w->ctx : w->base);
	return msg ? msg : "handshake failure";
}

static const char *start_worker(struct Worker *w, int fd)
{
	w->socket = fd;
	return do_handshake(w, fd);
}

static void ignore_sigpipe(void)
{
#ifndef WIN32
	static bool done;
	sigset_t set;
	int ret;

	if (done)
		return;

	/* block SIGPIPE */
	sigemptyset(&set);
	sigaddset(&set, SIGPIPE);
	ret = sigprocmask(SIG_BLOCK, &set, NULL);
	if (ret < 0)
		err(1, "sigprocmask");
	done = true;
#endif
}

static const char *run_case(struct Worker *client, struct Worker *server)
{
	struct event_base *base = NULL;
	int spair[2];
	const char *res;
	bool done = false;

	ignore_sigpipe();

	base = event_init();
	client->evbase = base;
	server->evbase = base;

	tt_assert(socketpair(AF_UNIX, SOCK_STREAM, 0, spair) == 0);
	tt_assert(socket_setup(spair[0], true));
	tt_assert(socket_setup(spair[1], true));

	str_check(start_worker(server, spair[0]), "OK");
	str_check(start_worker(client, spair[1]), "OK");

	while (client->ctx || server->ctx)
		tt_assert(event_base_loop(base, EVLOOP_ONCE) == 0);

	done = true;
end:
	event_del(&client->ev);
	event_del(&server->ev);
	event_base_free(base);
	res = check_errors(client, server);
	free_worker(client);
	free_worker(server);
	return done ? res : "fail";
}

/*
 * Actual testcases.
 */

#define SERVER1 "key=ssl/ca1_server1.key", "cert=ssl/ca1_server1.crt"
#define SERVER2 "key=ssl/ca2_server2.key", "cert=ssl/ca2_server2.crt"
#define CLIENT1 "key=ssl/ca1_client1.key", "cert=ssl/ca1_client1.crt"
#define CLIENT2 "key=ssl/ca2_client2.key", "cert=ssl/ca2_client2.crt"
#define CA1 "ca=ssl/ca1_root.crt"
#define CA2 "ca=ssl/ca2_root.crt"

static void test_verify(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* default: client checks server cert, succeeds */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* default: client checks server cert, fails due to bad ca */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA2, "host=example.com", NULL), "OK");
	str_check(run_case(client, server), "C:certificate verify failed - S:handshake failure");

	/* default: client checks server cert, fails due to bad hostname */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA1, "host=example2.com", NULL), "OK");
	str_check(run_case(client, server), "C:name 'example2.com' does not match cert");
end:;
}

static void test_noverifyname(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* noverifyname: client checks server cert, ignore bad hostname */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA1, "host=example2.com",
		"noverifyname=1",
		NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* noverifyname: client checks server cert, ignore NULL hostname */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA1, "noverifyname=1", NULL), "OK");
	str_check(run_case(client, server), "OK");
end:;
}

static void test_noverifycert(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* noverifycert: client ignores cert */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"host=server1.com",
		"noverifycert=1",
		NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* noverifycert: client ignores cert, but checks hostname */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"host=server2.com",
		"noverifycert=1",
		NULL), "OK");
	str_check(run_case(client, server), "C:name 'server2.com' does not match cert");

	/* noverifycert: client ignores both cert, hostname */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"host=server2.com",
		"noverifycert=1",
		"noverifyname=1",
		NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* noverifycert: client ignores both cert, hostname (=NULL) */
	str_check(create_worker(&server, true, SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"noverifycert=1",
		"noverifyname=1",
		NULL), "OK");
	str_check(run_case(client, server), "OK");
end:;
}

static void test_clientcert(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* ok: server checks server cert */
	str_check(create_worker(&server, true, SERVER1, CA2, NULL), "OK");
	str_check(create_worker(&client, false, CLIENT2, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* fail: server rejects invalid cert */
	str_check(create_worker(&server, true, SERVER1, CA1, NULL), "OK");
	str_check(create_worker(&client, false, CLIENT2, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "C:tlsv1 alert unknown ca - S:handshake failure");

	/* noverifycert: server allow invalid cert */
	str_check(create_worker(&server, true, SERVER1, CA1, "noverifycert=1", NULL), "OK");
	str_check(create_worker(&client, false, CLIENT2, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* allow client without cert */
	str_check(create_worker(&server, true, SERVER1, CA2, NULL), "OK");
	str_check(create_worker(&client, false, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "OK");
end:;
}

static void test_fingerprint(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* both server & client with cert */
	str_check(create_worker(&server, true, SERVER1, CA2,
		"peer-sha1=ssl/ca2_client2.crt.sha1",
		"peer-sha256=ssl/ca2_client2.crt.sha256",
		NULL), "OK");
	str_check(create_worker(&client, false, CLIENT2, CA1,
		"host=server1.com",
		"peer-sha1=ssl/ca1_server1.crt.sha1",
		"peer-sha256=ssl/ca1_server1.crt.sha256",
		NULL), "OK");
	str_check(run_case(client, server), "OK");

	/* client without cert */
	str_check(create_worker(&server, true, SERVER1, CA1,
		"peer-sha1=ssl/ca2_client2.crt.sha1",
		"peer-sha256=ssl/ca2_client2.crt.sha256",
		NULL), "OK");
	str_check(create_worker(&client, false, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "C:write!=3 - S:FP-sha1-fail");
end:;
}

static void test_set_mem(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* both server & client with cert */
	str_check(create_worker(&server, true, "mem=1", SERVER1, CA2, NULL), "OK");
	str_check(create_worker(&client, false, "mem=1", CLIENT2, CA1, "host=server1.com", NULL), "OK");
	str_check(run_case(client, server), "OK");
end:;
}

static void test_cipher_nego(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* server key is EC:secp384r1 - ECDHE-ECDSA */
	str_check(create_worker(&server, true, "show=ciphers", SERVER1, NULL), "OK");
	str_check(create_worker(&client, false, CA1,
		"ciphers=AESGCM",
		"host=server1.com",
		NULL), "OK");
	str_check(run_case(client, server), "TLSv1.2/ECDHE-ECDSA-AES256-GCM-SHA384/ECDH=secp384r1");

	/* server key is RSA - ECDHE-RSA */
	str_check(create_worker(&server, true, "show=ciphers", SERVER2, NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"ciphers=AESGCM",
		"host=server2.com",
		NULL), "OK");
	str_check(run_case(client, server), "TLSv1.2/ECDHE-RSA-AES256-GCM-SHA384/ECDH=prime256v1");

	/* server key is RSA - DHE-RSA */
	str_check(create_worker(&server, true, SERVER2,
		"show=ciphers",
		"dheparams=auto",
		NULL), "OK");
	str_check(create_worker(&client, false, CA2,
		"ciphers=EDH+AES",
		"host=server2.com",
		NULL), "OK");
	str_check(run_case(client, server), "TLSv1.2/DHE-RSA-AES256-GCM-SHA384/DH=2048");
end:;
}

static void test_cert_info(void *z)
{
	struct Worker *server = NULL, *client = NULL;

	tt_assert(tls_init() == 0);

	/* both server & client with cert */
	str_check(create_worker(&server, true, "show=peer-cert", SERVER1, CA2,
		"peer-sha1=ssl/ca2_client2.crt.sha1",
		"peer-sha256=ssl/ca2_client2.crt.sha256",
		NULL), "OK");
	str_check(create_worker(&client, false, CLIENT2, CA1,
		"host=server1.com",
		"peer-sha1=ssl/ca1_server1.crt.sha1",
		"peer-sha256=ssl/ca1_server1.crt.sha256",
		NULL), "OK");
	str_check(run_case(client, server),
		  "Subject: /CN=client2/C=XX/ST=State2/L=City2/O=Org2"
		  " Issuer: /CN=TestCA2"
		  " Serial: 164012649043499037638476466740783405990"
		  " NotBefore: 2010-01-01T08:05:00Z"
		  " NotAfter: 2060-12-31T23:55:00Z");

end:;
}

/*
 * Host name pattern matching.
 */


static const char *do_verify(const char *hostname, const char *commonName, ...)
{
#ifdef USUAL_LIBSSL_FOR_TLS
	struct tls ctx;
	struct tls_cert_info cert;
	struct tls_cert_alt_name names[20], *alt;
	union { struct in_addr ip4; struct in6_addr ip6; } addrbuf[20];
	int addrpos = 0, ret;
	va_list ap;
	const char *aname;

	memset(&ctx, 0, sizeof(ctx));
	memset(&addrbuf, 0, sizeof(addrbuf));
	memset(&cert, 0, sizeof(cert));
	memset(&names, 0, sizeof(names));

	cert.subject.common_name = commonName;
	cert.subject_alt_names = names;

	va_start(ap, commonName);
	while (1) {
		aname = va_arg(ap, char *);
		if (!aname)
			break;
		alt = &names[cert.subject_alt_name_count++];
		if (!memcmp(aname, "dns:", 4)) {
			alt->alt_name_type = TLS_CERT_NAME_DNS;
			alt->alt_name = aname + 4;
		} else if (!memcmp(aname, "ip4:", 4)) {
			alt->alt_name_type = TLS_CERT_NAME_IPv4;
			alt->alt_name = &addrbuf[addrpos++];
			if (inet_pton(AF_INET, aname + 4, (void*)alt->alt_name) != 1)
				return aname;
		} else if (!memcmp(aname, "ip6:", 4)) {
			alt->alt_name_type = TLS_CERT_NAME_IPv6;
			alt->alt_name = &addrbuf[addrpos++];
			if (inet_pton(AF_INET6, aname + 4, (void*)alt->alt_name) != 1)
				return aname;
		} else {
			return aname;
		}
	}
	va_end(ap);

	ret = tls_check_servername(&ctx, &cert, hostname);
	if (ctx.errmsg)
		free(ctx.errmsg);
	if (ret == 0)
		return "OK";
	if (ret == -1)
		return "FAIL";
#endif
	return "Unexpected code";
}

static void test_servername(void *_)
{
	str_check(do_verify("localhost", NULL, NULL), "FAIL");
	str_check(do_verify("www.foo.com", "foo.com", "dns:foo.com", "dns:www.foo.com", NULL), "OK");
	str_check(do_verify("foo.com", "foo.com", "dns:foo.com", "dns:www.foo.com", NULL), "OK");
	str_check(do_verify("faa.com", "foo.com", "dns:foo.com", "dns:www.foo.com", NULL), "FAIL");

	str_check(do_verify("www.foo.com", "*.foo.com", NULL), "OK");
	str_check(do_verify("foo.com", "*.foo.com", NULL), "FAIL");
	str_check(do_verify("foo.com", ".foo.com", NULL), "FAIL");
	str_check(do_verify("foo.co.uk", "*.co.uk", NULL), "OK");
	str_check(do_verify("www.foo.com", "w*.foo.com", NULL), "FAIL");
	str_check(do_verify("www.foo.com", "www.*.com", NULL), "FAIL");
	str_check(do_verify("www.foo.com", "*", NULL), "FAIL");
	str_check(do_verify("www.foo.com", "*.*.*", NULL), "FAIL");
	str_check(do_verify("foo.com", "*.com", NULL), "FAIL");
	str_check(do_verify("foo.com", "*.org", NULL), "FAIL");
	str_check(do_verify("localhost", "*", NULL), "FAIL");

	str_check(do_verify("foo.com", "foox.com", "ip4:11.11.11.11", "ip6:fefe::efef", "dns:foo.com", NULL), "OK");
	str_check(do_verify("11.11.11.11", "foo.com", "ip4:11.11.11.11", "ip6:fefe::efef", NULL), "OK");
	str_check(do_verify("11.11.11.12", "foo.com", "ip4:11.11.11.11", "ip6:fefe::efef", NULL), "FAIL");
	str_check(do_verify("fefe::efef", "foo.com", "ip4:11.11.11.11", "ip6:fefe::efef", NULL), "OK");
	str_check(do_verify("fefe::efff", "foo.com", "ip4:11.11.11.11", "ip6:fefe::efef", NULL), "FAIL");

	str_check(do_verify("127.0.0.1", "foo.com", "ip4:127.0.0.1", NULL), "OK");
	str_check(do_verify("127.0.0.1", "*.0.0.1", NULL), "FAIL");
	str_check(do_verify("127.0.0.1", "127.0.0.*", NULL), "FAIL");
	str_check(do_verify("fefe::efef", "*.efef", NULL), "FAIL");
	str_check(do_verify("fefe::efef", "fefe::efef", NULL), "OK");
	str_check(do_verify("fefe::efef", "foo", "dns:fefe::efef", NULL), "FAIL");
	str_check(do_verify("1.1.1.1", "1.1.1.1", NULL), "OK");
	str_check(do_verify("1.1.1.1", NULL, "dns:1.1.1.1", NULL), "FAIL");
end:;
}

struct testcase_t tls_tests[] = {
#ifndef USUAL_LIBSSL_FOR_TLS
	END_OF_TESTCASES,
#endif
	{ "verify", test_verify },
	{ "noverifyname", test_noverifyname },
	{ "noverifycert", test_noverifycert },
	{ "clientcert", test_clientcert },
	{ "fingerprint", test_fingerprint },
	{ "servername", test_servername },
	{ "set-mem", test_set_mem },
	{ "cipher-nego", test_cipher_nego },
	{ "cert-info", test_cert_info },
	END_OF_TESTCASES
};

