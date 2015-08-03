/* $OpenBSD: tls_verify.c,v 1.7 2015/02/11 06:46:33 jsing Exp $ */
/*
 * Copyright (c) 2014 Jeremie Courreges-Anglas <jca@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "tls_compat.h"

#ifdef USUAL_LIBSSL_FOR_TLS

#include <openssl/x509v3.h>

#include "tls_internal.h"

static int
tls_get_subj_string(X509_NAME *subject, int nid, const char **str_p, int *len_p)
{
	char *res = NULL;
	int res_len;

	res_len = X509_NAME_get_text_by_NID(subject, nid, NULL, 0);
	if (res_len < 0) {
		if (len_p) *len_p = 0;
		if (str_p) *str_p = NULL;
		return 0;
	}

	if (len_p)
		*len_p = res_len;

	if (!str_p)
		return res_len;

	res = calloc(res_len + 1, 1);
	if (res == NULL)
		return -1;

	X509_NAME_get_text_by_NID(subject, nid, res, res_len + 1);

	/* NUL bytes in value? */
	if ((size_t)res_len != strlen(res)) {
		free(res);
		return -1;
	}

	*str_p = res;
	return 0;
}

void
tls_cert_free(struct tls_cert_info *cert)
{
	int i;
	if (!cert)
		return;
	free(cert->common_name);
	free(cert->country_name);
	free(cert->locality_name);
	free(cert->state_or_province_name);
	free(cert->organization_name);
	free(cert->organizational_unit_name);
	if (cert->altname_count) {
		for (i = 0; i < cert->altname_count; i++)
			free(cert->altnames[i].alt_name);
	}
	free(cert->altnames);
	free(cert);
}

/* See RFC 5280 section 4.2.1.6 for SubjectAltName details. */
static int
fill_altname(struct tls_cert_info *cert_info, X509 *x509_cert)
{
	STACK_OF(GENERAL_NAME) *altname_stack = NULL;
	GENERAL_NAME *altname;
	int count, i, format, len;
	struct tls_cert_alt_name *slot;
	void *data;
	int rv = -1;

	altname_stack = X509_get_ext_d2i(x509_cert, NID_subject_alt_name, NULL, NULL);
	if (altname_stack == NULL)
		return 0;

	count = sk_GENERAL_NAME_num(altname_stack);
	if (count == 0)
		return 0;

	cert_info->altnames = calloc(sizeof (struct tls_cert_alt_name), count);
	if (cert_info->altnames == NULL)
		return -1;

	for (i = 0; i < count; i++) {
		slot = &cert_info->altnames[cert_info->altname_count];
		altname = sk_GENERAL_NAME_value(altname_stack, i);

		if (altname->type == GEN_DNS) {
			format = ASN1_STRING_type(altname->d.dNSName);
			if (format != V_ASN1_IA5STRING)
				goto failed;
			data = ASN1_STRING_data(altname->d.dNSName);
			len = ASN1_STRING_length(altname->d.dNSName);
			if (len < 0 || (size_t)len != strlen(data))
				goto failed;

			/*
			 * Per RFC 5280 section 4.2.1.6:
			 * " " is a legal domain name, but that
			 * dNSName must be rejected.
			 */
			if (strcmp(data, " ") == 0)
				goto failed;

			slot->alt_name = strdup(data);
			if (slot->alt_name == NULL)
				goto failed;
			slot->alt_name_type = TLS_CERT_NAME_DNS;
			cert_info->altname_count++;
		} else if (altname->type == GEN_IPADD) {
			len = ASN1_STRING_length(altname->d.iPAddress);
			data = ASN1_STRING_data(altname->d.iPAddress);
			if (len < 0)
				goto failed;

			/*
			 * Per RFC 5280 section 4.2.1.6:
			 * IPv4 must use 4 octets and IPv6 must use 16 octets.
			 */
			if (len == 4) {
				slot->alt_name_type = TLS_CERT_NAME_IPv4;
			} else if (len == 16) {
				slot->alt_name_type = TLS_CERT_NAME_IPv6;
			} else {
				goto failed;
			}
			slot->alt_name = malloc(len);
			if (slot->alt_name == NULL)
				goto failed;
			memcpy((void *)slot->alt_name, data, len);
			cert_info->altname_count++;
		} else {
			/* ignore unknown types */
		}
	}
	rv = 0;
failed:
	sk_GENERAL_NAME_pop_free(altname_stack, GENERAL_NAME_free);
	return rv;
}

int
tls_get_peer_cert(struct tls *ctx, struct tls_cert_info **cert_p)
{
	struct tls_cert_info *cert = NULL;
	SSL *conn = ctx->ssl_conn;
	X509 *peer;
	X509_NAME *subject;

	*cert_p = NULL;
	if (!conn)
		return 0;

	peer = SSL_get_peer_certificate(conn);
	if (!peer)
		return 0;

	cert = calloc(sizeof *cert, 1);
	if (!cert)
		return -1;

	subject = X509_get_subject_name(peer);
	if (!subject)
		goto failed;

	if (tls_get_subj_string(subject, NID_commonName, &cert->common_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_countryName, &cert->country_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_localityName, &cert->locality_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_stateOrProvinceName, &cert->state_or_province_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_organizationName, &cert->organization_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_organizationalUnitName, &cert->organizational_unit_name, NULL) < 0)
		goto failed;
	if (tls_get_subj_string(subject, NID_pkcs9_emailAddress, &cert->email_address, NULL) < 0)
		goto failed;

	if (fill_altname(cert, peer) < 0)
		goto failed;

	*cert_p = cert;
	return 0;

failed:
	tls_cert_free(cert);
	return -1;
}

#endif
