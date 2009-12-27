/*
 * Async Postgres connection.
 *
 * Copyright (c) 2009  Marko Kreen
 *
 * Permission to use, copy, modify, and/or distribute this software for any
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

#ifndef _USUAL_PGSOCKET_H_
#define _USUAL_PGSOCKET_H_

#include <usual/base.h>

#include <libpq-fe.h>

enum PgEvent {
	PGS_CONNECT_OK,
	PGS_CONNECT_FAILED,
	PGS_RESULT_OK,
	PGS_RESULT_BAD,
	PGS_TIMEOUT,
};

struct PgSocket;
struct event_base;

typedef void (*pgs_handler_f)(struct PgSocket *pgs, void *arg, enum PgEvent dbev, PGresult *res);

struct PgSocket *pgs_create(const char *connstr, pgs_handler_f fn, void *arg);
void pgs_free(struct PgSocket *db);

void pgs_set_event_base(struct PgSocket *pgs, struct event_base *base);

void pgs_connect(struct PgSocket *db);
void pgs_disconnect(struct PgSocket *db);

void pgs_send_query_simple(struct PgSocket *db, const char *query);
void pgs_send_query_params(struct PgSocket *db, const char *query, int nargs, ...);
void pgs_send_query_params_list(struct PgSocket *db, const char *query, int nargs, const char *argv[]);

void pgs_sleep(struct PgSocket *db, double timeout);
void pgs_reconnect(struct PgSocket *db, double timeout);

int pgs_connection_valid(struct PgSocket *db);

PGconn *pgs_get_connection(struct PgSocket *db);

#endif

