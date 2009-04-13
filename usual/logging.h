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

#ifndef _USUAL_LOGGING_H_
#define _USUAL_LOGGING_H_

#include <usual/base.h>

#include <stdlib.h>

/*
 * 0 - show only info level msgs (default)
 * 1 - show debug msgs (log_debug)
 * 2 - show noise msgs (log_noise)
 */
extern int cf_verbose;

/* If logging to stdout is allowed (default: 1) */
/* daemon.c turns this off if goes to background */
extern int cf_quiet;

/* logfile location, default NULL */
extern const char *cf_logfile;

/* ident for syslog, if NULL syslog is disabled (default) */
extern const char *cf_syslog_ident;

/*
 * Quick API overview:
 *
 * void log_error(const char *s, ...);
 * void log_warning(const char *s, ...);
 * void log_info(const char *s, ...);
 * void log_debug(const char *s, ...);
 * void log_noise(const char *s, ...);
 * void fatal(const char *s, ...);
 * void fatal_perror(const char *s, ...);
 * void die(const char *s, ...);
 *
 * close_logfile(void);
 */

/*
 * Internal logging function.
 */
enum LogLevel {
	LG_FATAL = 0,
	LG_ERROR = 1,
	LG_WARNING = 2,
	LG_INFO = 3,
	LG_DEBUG = 4,
	LG_NOISE = 5,
};
void log_generic(enum LogLevel level, const char *s, ...) _PRINTF(2, 3);

/* macros for plain logging */
#define log_error(args...) log_generic(LG_ERROR, ## args)
#define log_warning(args...) log_generic(LG_WARNING, ## args)
#define log_info(args...) log_generic(LG_INFO, ## args)

/* move printf arg setup out-of-line for debug macros */
#define log_debug(args...) do { \
		if (unlikely(cf_verbose > 0)) \
			log_generic(LG_DEBUG, ## args); \
	} while (0)
#define log_noise(args...) do { \
		if (unlikely(cf_verbose > 1)) \
			log_generic(LG_NOISE, ## args); \
	} while (0)

/* this is also defined in base.h for Assert() */
void log_fatal(const char *file, int line, const char *func, bool show_perror, const char *s, ...) _PRINTF(5, 6);

/* fatal loggers should also log location */
#define fatal(args...) do { \
	log_fatal(__FILE__, __LINE__, __func__, false, ## args); \
	exit(1); } while (0)
#define fatal_perror(args...) do { \
	log_fatal(__FILE__, __LINE__, __func__, true, ## args); \
	exit(1); } while (0)

/* less verbose fatal() */
#define die(msg, args...) do { \
	log_generic(LG_FATAL, msg, ## args); \
	exit(1); } while (0)

void reset_logging(void);

#endif

