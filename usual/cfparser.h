/*
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

/** @file
 * Config file parser.
 */
#ifndef _USUAL_CFPARSER_H_
#define _USUAL_CFPARSER_H_

#include <usual/base.h>

/**
 * @name Simple line-by-line parser
 * @{
 */

/**
 * Parsed line type.
 */
enum CfKeyType {
	CF_SECT,	/**< Section */
	CF_KEY		/**< Parameter */
};

/** Callback signarure for @ref parse_ini_file() */
typedef bool (*cf_handler_f)(void *arg, enum CfKeyType, const char *key, const char *val);

/**
 * Simple parser, launches callback for each line
 */
bool parse_ini_file(const char *fn, cf_handler_f user_handler, void *arg) _MUSTCHECK;

/* @} */

/**
 * @name Complex parser with variable setting.
 * @{
 */

/**
 * Callback for section initialization
 */
typedef void *(*cf_create_target_f)(void *top_arg, const char *sect_name);

/**
 * Callback for setting a variable
 */
typedef bool (*cf_setter_f)(void *dst_p, const char *value);

/**
 * Parameter description
 */
struct CfKey {
	/** Parameter name */
	const char *key_name;
	/** Setter function, called wit absolute pointer */
	cf_setter_f set_fn;
	/** Flags: CF_VAL_ABS, CF_VAL_REL */
	int flags;
	/** Absolute or relative offset */
	uintptr_t key_ofs;
	/** Default value as string */
	const char *def_value;
};

/** The pointer is relative to base */
#define CF_VAL_REL 1
/** The pointer is absolute */
#define CF_VAL_ABS 2

/**
 * Section description
 */
struct CfSect {
	/** Section name */
	const char *sect_name;
	/** Section creation function (optional) */
	cf_create_target_f create_target_fn;
	/** Key list */
	const struct CfKey *key_list;
};

/** Setter for string */
bool cf_set_str(void *dst, const char *value);
/** Setter for filename */
bool cf_set_filename(void *dst, const char *value);
/** Setter for int */
bool cf_set_int(void *dst, const char *value);
/** Setter for time-usec */
bool cf_set_time_usec(void *dst, const char *value);
/** Setter for time-double */
bool cf_set_time_double(void *dst, const char *value);

/* before using them do: #define CF_REL_BASE struct Foo */
/* later: #undef CF_REL_BASE */

/** Integer with offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_INT(x) cf_set_int, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** String with offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_STR(x) cf_set_str, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** Filename with offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_FILENAME(x) cf_set_filename, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** Integer offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_BOOL(x) cf_set_int, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** Integer offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_TIME_USEC(x) cf_set_time_usec, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** Integer offset relative to struct referenced in CF_REL_BASE */
#define CF_REL_TIME_DOUBLE(x) cf_set_time_double, CF_VAL_REL, offsetof(CF_REL_BASE, x)

/** Integer with absolute pointer */
#define CF_ABS_INT(x) cf_set_int, CF_VAL_ABS, (uintptr_t)&(x)

/** String with absolute pointer */
#define CF_ABS_STR(x) cf_set_str, CF_VAL_ABS, (uintptr_t)&(x)

/** Filename with absolute pointer */
#define CF_ABS_FILENAME(x) cf_set_filename, CF_VAL_ABS, (uintptr_t)&(x)

/** Bool with absolute pointer */
#define CF_ABS_BOOL(x) cf_set_int, CF_VAL_ABS, (uintptr_t)&(x)

/** Time in seconds stored in usec_t */
#define CF_ABS_TIME_USEC(x) cf_set_time_usec, CF_VAL_ABS, (uintptr_t)&(x)

/** Time in second as double */
#define CF_ABS_TIME_DOUBLE(x) cf_set_time_double, CF_VAL_ABS, (uintptr_t)&(x)

/**
 * Main entry point
 */
bool load_ini_file(const char *fn, const struct CfSect *sect_list, void *top_arg) _MUSTCHECK;

/* @} */

#endif
