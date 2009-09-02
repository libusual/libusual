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

#include <usual/pgsocket.h>

#include <stdarg.h>

#include <usual/event.h>
#include <usual/logging.h>
#include <usual/time.h>
#include <usual/string.h>

/* PgSocket.wait_type */
#define W_NONE 0
#define W_SOCK 1
#define W_TIME 2

typedef void (*libev_cb)(int sock, short flags, void *arg);

struct PgSocket {
	struct event ev;

	unsigned wait_type:4;

	PGconn *con;

	pgs_handler_f handler_func;
	void *handler_arg;

	const char *connstr;

	struct event_base *base;
};

static void send_event(struct PgSocket *db, enum PgEvent ev)
{
	db->handler_func(db, db->handler_arg, ev, NULL);
}

static void wait_event(struct PgSocket *db, short ev, libev_cb fn)
{
	Assert(!db->wait_type);

	event_set(&db->ev, PQsocket(db->con), ev, fn, db);
	if (db->base)
		event_base_set(db->base, &db->ev);
	if (event_add(&db->ev, NULL) < 0)
		fatal_perror("event_add");

	db->wait_type = W_SOCK;
}

static void timeout_cb(int sock, short flags, void *arg)
{
	struct PgSocket *db = arg;

	db->wait_type = 0;

	send_event(db, PGS_TIMEOUT);
}

/* some error happened */
static void conn_error(struct PgSocket *db, enum PgEvent ev, const char *desc)
{
	log_error("connection error: %s", desc);
	log_error("libpq: %s", PQerrorMessage(db->con));
	send_event(db, ev);
}

/*
 * Called when select() told that conn is avail for reading/writing.
 *
 * It should call postgres handlers and then change state if needed.
 */
static void result_cb(int sock, short flags, void *arg)
{
	struct PgSocket *db = arg;
	PGresult *res, *res_saved = NULL;

	db->wait_type = 0;

	if (!PQconsumeInput(db->con)) {
		conn_error(db, PGS_RESULT_BAD, "PQconsumeInput");
		return;
	}

	/* loop until PQgetResult returns NULL */
	while (1) {
		/* incomplete result? */
		if (PQisBusy(db->con)) {
			wait_event(db, EV_READ, result_cb);
			return;
		}

		/* next result */
		res = PQgetResult(db->con);
		if (!res)
			break;

		if (res_saved) {
			PQclear(res_saved);
		}
		res_saved = res;
	}

	db->handler_func(db, db->handler_arg, PGS_RESULT_OK, res_saved);
}

static void send_cb(int sock, short flags, void *arg)
{
	int res;
	struct PgSocket *db = arg;

	db->wait_type = 0;

	res = PQflush(db->con);
	if (res > 0) {
		wait_event(db, EV_WRITE, send_cb);
	} else if (res == 0) {
		wait_event(db, EV_READ, result_cb);
	} else
		conn_error(db, PGS_RESULT_BAD, "PQflush");
}


static void connect_cb(int sock, short flags, void *arg)
{
	struct PgSocket *db = arg;
	PostgresPollingStatusType poll_res;

	db->wait_type = 0;

	poll_res = PQconnectPoll(db->con);
	switch (poll_res) {
	case PGRES_POLLING_WRITING:
		wait_event(db, EV_WRITE, connect_cb);
		break;
	case PGRES_POLLING_READING:
		wait_event(db, EV_READ, connect_cb);
		break;
	case PGRES_POLLING_OK:
		send_event(db, PGS_CONNECT_OK);
		break;
	default:
		conn_error(db, PGS_CONNECT_FAILED, "PQconnectPoll");
	}
}

/*
 * Public API
 */

struct PgSocket *pgs_create(const char *connstr, pgs_handler_f fn, void *handler_arg)
{
	struct PgSocket *db;

	db = zmalloc(sizeof(*db));
	if (!db)
		return NULL;

	db->handler_func = fn;
	db->handler_arg = handler_arg;

	db->connstr = strdup(connstr);
	if (!db->connstr) {
		pgs_free(db);
		return NULL;
	}
	return db;
}

void pgs_set_event_base(struct PgSocket *pgs, struct event_base *base)
{
	pgs->base = base;
}

void pgs_connect(struct PgSocket *db)
{
	db->con = PQconnectStart(db->connstr);
	if (db->con == NULL) {
		conn_error(db, PGS_CONNECT_FAILED, "PQconnectStart");
		return;
	}

	if (PQstatus(db->con) == CONNECTION_BAD) {
		conn_error(db, PGS_CONNECT_FAILED, "PQconnectStart");
		return;
	}

	wait_event(db, EV_WRITE, connect_cb);
}


void pgs_disconnect(struct PgSocket *db)
{
	if (db->con) {
		PQfinish(db->con);
		db->con = NULL;
	}
}

void pgs_free(struct PgSocket *db)
{
	if (db) {
		pgs_disconnect(db);
		free(db->connstr);
		free(db);
	}
}

void pgs_sleep(struct PgSocket *db, double timeout)
{
	struct timeval tv;

	Assert(!db->wait_type);

	tv.tv_sec = timeout;
	tv.tv_usec = (timeout - tv.tv_sec) * USEC;

	evtimer_set(&db->ev, timeout_cb, db);
	if (db->base)
		event_base_set(db->base, &db->ev);
	//event_assign(&db->ev, db->base, -1, 0, timeout_cb, db);
	if (evtimer_add(&db->ev, &tv) < 0)
		fatal_perror("event_add");

	db->wait_type = W_TIME;
}

void pgs_reconnect(struct PgSocket *db)
{
	pgs_disconnect(db);
	pgs_sleep(db, 60);
}

void pgs_send_query_simple(struct PgSocket *db, const char *q)
{
	int res;

	log_debug("%s", q);
	res = PQsendQuery(db->con, q);
	if (!res) {
		conn_error(db, PGS_RESULT_BAD, "PQsendQuery");
		return;
	}

	res = PQflush(db->con);
	if (res > 0) {
		wait_event(db, EV_WRITE, send_cb);
	} else if (res == 0) {
		wait_event(db, EV_READ, result_cb);
	} else
		conn_error(db, PGS_RESULT_BAD, "PQflush");
}

void pgs_send_query_params(struct PgSocket *db, const char *q, int cnt, ...)
{
	int i;
	va_list ap;
	const char * args[10];

	if (cnt > 10) cnt = 10;

	va_start(ap, cnt);
	for (i = 0; i < cnt; i++)
		args[i] = va_arg(ap, char *);
	va_end(ap);

	pgs_send_query_params_list(db, q, cnt, args);
}

void pgs_send_query_params_list(struct PgSocket *db, const char *q, int cnt, const char *args[])
{
	int res;

	res = PQsendQueryParams(db->con, q, cnt, NULL, args, NULL, NULL, 0);
	if (!res) {
		conn_error(db, PGS_RESULT_BAD, "PQsendQueryParams");
		return;
	}

	res = PQflush(db->con);
	if (res > 0) {
		wait_event(db, EV_WRITE, send_cb);
	} else if (res == 0) {
		wait_event(db, EV_READ, result_cb);
	} else
		conn_error(db, PGS_RESULT_BAD, "PQflush");
}

int pgs_connection_valid(struct PgSocket *db)
{
	return (db->con != NULL);
}

PGconn *pgs_get_connection(struct PgSocket *db)
{
	return db->con;
}

