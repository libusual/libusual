/*
 * Config file parser.
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

#ifndef _USUAL_CFPARSER_H_
#define _USUAL_CFPARSER_H_

#include <usual/base.h>

/*
 * Simple line-by-line parser
 */

enum CfKeyType {
	CF_SECT,
	CF_KEY
};

typedef bool (*cf_handler_f)(void *arg, enum CfKeyType, const char *key, const char *val);

bool parse_ini_file(const char *fn, cf_handler_f user_handler, void *arg) _MUSTCHECK;

/*
 * Fancier one.
 */

typedef void *(*cf_create_target_f)(void *top_arg, const char *sect_name);
typedef bool (*cf_setter_f)(void *dst_p, const char *value);

struct CfKey {
	const char *key_name;
	cf_setter_f set_fn;
	int flags;
	uintptr_t key_ofs;
	const char *def_value;
};

/* abs or relative pointer */
#define CF_VAL_REL 1
#define CF_VAL_ABS 2

struct CfSect {
	const char *sect_name;
	cf_create_target_f create_target_fn;
	const struct CfKey *key_list;
};

bool load_ini_file(const char *fn, const struct CfSect *sect_list, void *top_arg) _MUSTCHECK;

bool cf_set_str(void *dst, const char *value);
bool cf_set_int(void *dst, const char *value);
bool cf_set_time_usec(void *dst, const char *value);
bool cf_set_time_double(void *dst, const char *value);

/* before using them do: #define CF_REL_BASE struct Foo */
#define CF_REL_INT(x) cf_set_int, CF_VAL_REL, offsetof(CF_REL_BASE, x)
#define CF_REL_STR(x) cf_set_str, CF_VAL_REL, offsetof(CF_REL_BASE, x)
#define CF_REL_BOOL(x) cf_set_int, CF_VAL_REL, offsetof(CF_REL_BASE, x)
#define CF_REL_TIME_USEC(x) cf_set_time_usec, CF_VAL_REL, offsetof(CF_REL_BASE, x)
#define CF_REL_TIME_DOUBLE(x) cf_set_time_double, CF_VAL_REL, offsetof(CF_REL_BASE, x)
/* later: #undef CF_REL_BASE */

#define CF_ABS_INT(x) cf_set_int, CF_VAL_ABS, (uintptr_t)&(x)
#define CF_ABS_STR(x) cf_set_str, CF_VAL_ABS, (uintptr_t)&(x)
#define CF_ABS_BOOL(x) cf_set_int, CF_VAL_ABS, (uintptr_t)&(x)
#define CF_ABS_TIME_USEC(x) cf_set_time_usec, CF_VAL_ABS, (uintptr_t)&(x)
#define CF_ABS_TIME_DOUBLE(x) cf_set_time_double, CF_VAL_ABS, (uintptr_t)&(x)

#endif
