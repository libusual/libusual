/*
 * Logging for unix service.
 *
 * Copyright (c) 2007-2009 Marko Kreen, Skype Technologies OÜ
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

#include <usual/logging.h>

#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include <usual/time.h>

int cf_quiet = 0;
int cf_verbose = 0;
const char *cf_logfile = NULL;
const char *cf_syslog_ident = NULL;

static FILE *log_file = NULL;
static bool syslog_started = false;

struct LevelInfo {
	const char *tag;
	int syslog_prio;
};

static const struct LevelInfo log_level_list[] = {
	{ "FATAL", LOG_CRIT },
	{ "ERROR", LOG_ERR },
	{ "WARNING", LOG_WARNING },
	{ "LOG", LOG_INFO },
	{ "DEBUG", LOG_DEBUG },
	{ "NOISE", LOG_DEBUG },
};

void reset_logging(void)
{
	if (log_file) {
		fclose(log_file);
		log_file = NULL;
	}
	if (syslog_started) {
		closelog();
		syslog_started = 0;
	}
}


static void start_syslog(void)
{
	openlog(cf_syslog_ident, LOG_PID, LOG_DAEMON);
	syslog_started = 1;
}


void log_generic(enum LogLevel level, const char *fmt, ...)
{
	char buf[2048];
	char timebuf[64];
	const struct LevelInfo *lev = &log_level_list[level];
	unsigned pid = getpid();

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	format_time_ms(NULL, timebuf, sizeof(timebuf));

	if (!log_file && cf_logfile) {
		static int error_reported = 0;

		if ((log_file = fopen(cf_logfile, "a")) != NULL) {
			/* Got the file, disable buffering */
			setvbuf(log_file, NULL, _IONBF, 0);
		} else if (!cf_quiet && !error_reported) {
			/* Unable to open, complain once */
			fprintf(stderr, "%s %u %s %s: %s\n", timebuf, pid,
				log_level_list[2].tag, cf_logfile, strerror(errno));
			error_reported = 1;
		}
	}

	if (!cf_quiet)
		fprintf(stderr, "%s %u %s %s\n", timebuf, pid, lev->tag, buf);

	if (log_file)
		fprintf(log_file, "%s %u %s %s\n", timebuf, pid, lev->tag, buf);

	if (cf_syslog_ident) {
		if (!syslog_started)
			start_syslog();
		syslog(lev->syslog_prio, "%s", buf);
	}
}


void log_fatal(const char *file, int line, const char *func, bool show_perror, const char *fmt, ...)
{
	char buf[2048];
	const char *estr = NULL;
	int old_errno = 0;
	va_list ap;

	if (show_perror) {
		old_errno = errno;
		estr = strerror(errno);
	}

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	if (show_perror) {
		log_generic(LG_FATAL, "@%s:%d in function %s(): %s: %s [%d]",
			     file, line, func, buf, estr, old_errno);
	} else {
		log_generic(LG_FATAL, "@%s:%d in function %s(): %s",
			     file, line, func, buf);
	}
}

