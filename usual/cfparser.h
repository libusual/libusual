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

typedef void *(*cf_create_target_f)(void *top_arg);
typedef bool (*cf_setter_f)(void *dst_p, const char *value);

struct CfKey {
	const char *key_name;
	cf_setter_f set_fn;
	unsigned key_ofs;
	const char *def_value;
};

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

#endif
