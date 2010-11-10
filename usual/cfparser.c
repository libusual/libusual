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

#include <usual/cfparser.h>

#include <ctype.h>
#include <string.h>
#include <pwd.h>

#include <usual/fileutil.h>
#include <usual/logging.h>
#include <usual/time.h>

/*
 * INI file parser.
 */

static int count_lines(const char *s, const char *end)
{
	int lineno = 1;
	for (; s < end; s++) {
		if (*s == '\n')
			lineno++;
	}
	return lineno;
}

bool parse_ini_file(const char *fn, cf_handler_f user_handler, void *arg)
{
	char *buf;
	char *p, *key, *val;
	int klen, vlen;
	char o1, o2;
	bool ok;

	buf = load_file(fn, NULL);
	if (buf == NULL)
		return false;

	p = buf;
	while (*p) {
		/* space at the start of line - including empty lines */
		while (*p && isspace(*p)) p++;

		/* skip comment lines */
		if (*p == '#' || *p == ';') {
			while (*p && *p != '\n') p++;
			continue;
		}
		/* got new section */
		if (*p == '[') {
			key = ++p;
			while (*p && *p != ']' && *p != '\n') p++;
			if (*p != ']')
				goto syntax_error;
			o1 = *p;
			*p = 0;

			log_debug("parse_ini_file: [%s]", key);
			ok = user_handler(arg, CF_SECT, key, NULL);
			*p++ = o1;
			if (!ok)
				goto failed;
			continue;
		}

		/* done? */
		if (*p == 0)
			break;

		/* read key val */
		key = p;
		while (*p && (isalnum(*p) || strchr("_.-*", *p))) p++;
		klen = p - key;

		/* expect '=', skip it */
		while (*p && (*p == ' ' || *p == '\t')) p++;
		if (*p != '=') {
			goto syntax_error;
		} else
			p++;
		while (*p && (*p == ' ' || *p == '\t')) p++;

		/* now read value */
		val = p;
		while (*p && (*p != '\n'))
			p++;
		vlen = p - val;
		/* eat space at end */
		while (vlen > 0 && isspace(val[vlen - 1]))
			vlen--;

		/* skip junk */
		while (*p && isspace(*p)) p++;

		/* our buf is r/w, so take it easy */
		o1 = key[klen];
		o2 = val[vlen];
		key[klen] = 0;
		val[vlen] = 0;

		log_debug("parse_ini_file: '%s' = '%s'", key, val);

		ok = user_handler(arg, CF_KEY, key, val);

		/* restore data, to keep count_lines() working */
		key[klen] = o1;
		val[vlen] = o2;

		if (!ok)
			goto failed;
	}

	free(buf);
	return true;

syntax_error:
	log_error("syntax error in configuration (%s:%d), stopping loading", fn, count_lines(buf, p));
failed:
	free(buf);
	return false;
}

struct LoaderCtx {
	const struct CfSect *sect_list;
	const struct CfSect *cur_sect;
	void *target;
	void *top_arg;
};

static void *get_dest(struct LoaderCtx *ctx, const struct CfKey *k)
{
	char *dst;
	if (k->flags & CF_VAL_REL) {
		if (!ctx->target)
			return NULL;
		dst = (char *)ctx->target + k->key_ofs;
	} else
		dst = (char *)k->key_ofs;
	return dst;
}

static bool fill_defaults(struct LoaderCtx *ctx)
{
	const struct CfKey *k;
	void *dst;
	for (k = ctx->cur_sect->key_list; k->key_name; k++) {
		if (!k->def_value)
			continue;
		dst = get_dest(ctx, k);
		if (!dst)
			return false;
		if (!k->set_fn(dst, k->def_value))
			return false;
	}
	return true;
}

static bool load_handler(void *arg, enum CfKeyType ktype, const char *key, const char *val)
{
	struct LoaderCtx *ctx = arg;
	const struct CfSect *s;
	const struct CfKey *k;
	void *dst;

	if (ktype == CF_SECT) {
		for (s = ctx->sect_list; s->sect_name; s++) {
			if (strcmp(s->sect_name, key) != 0
			    && strcmp(s->sect_name, "*") != 0)
				continue;
			ctx->cur_sect = s;
			if (s->create_target_fn)
				ctx->target = s->create_target_fn(ctx->top_arg, key);
			else
				ctx->target = ctx->top_arg;
			return fill_defaults(ctx);
		}
		log_error("load_init_file: unknown section: %s", key);
		return false;
	} else if (!ctx->cur_sect) {
		log_error("load_init_file: value without section: %s", key);
		return false;
	} else {
		for (k = ctx->cur_sect->key_list; k->key_name; k++) {
			if (strcmp(k->key_name, key) != 0)
				continue;
			dst = get_dest(ctx, k);
			if (!dst)
				return false;
			return k->set_fn(dst, val);
		}
		log_error("load_init_file: unknown key: %s", key);
		return false;
	}

	return true;
}

bool load_ini_file(const char *fn, const struct CfSect *sect_list, void *top_arg)
{
	struct LoaderCtx ctx = {
		.top_arg = top_arg,
		.sect_list = sect_list,
		.cur_sect = NULL,
		.target = NULL,
	};

	return parse_ini_file(fn, load_handler, &ctx);
}

/*
 * Various value parsers.
 */

bool cf_set_int(void *dst, const char *value)
{
	int *ptr = dst;
	*ptr = atoi(value);
	return true;
}

bool cf_set_str(void *dst, const char *value)
{
	char **dst_p = dst;

	char *tmp = strdup(value);
	if (!tmp)
		return false;
	if (*dst_p)
		free(*dst_p);
	*dst_p = tmp;
	return true;
}

bool cf_set_filename(void *dst, const char *value)
{
	char **dst_p = dst;
	char *tmp, *home, *p;
	int v_len, usr_len, home_len;
	struct passwd *pw;

	/* do we need to do tilde expansion */
	if (value[0] != '~')
		return cf_set_str(dst, value);

	/* find username end */
	v_len = strlen(value);
	if ((p = memchr(value, '/', v_len)) == NULL)
		usr_len = v_len - 1;
	else
		usr_len = (p - value) - 1;

	if (usr_len) {
		p = malloc(usr_len + 1);
		if (!p)
			return false;
		memcpy(p, value + 1, usr_len);
		p[usr_len] = 0;
		pw = getpwnam(p);
		free(p);
		if (!pw)
			goto fail;
		home = pw->pw_dir;
	} else {
		home = getenv("HOME");
		if (!home) {
			pw = getpwuid(getuid());
			if (!pw)
				goto fail;
			home = pw->pw_dir;
		}
	}
	if (!home)
		goto fail;

	home_len = strlen(home);
	tmp = malloc(v_len - usr_len + home_len);
	if (!tmp)
		return false;
	memcpy(tmp, home, home_len);
	memcpy(tmp + home_len, value + usr_len + 1, v_len - usr_len - 1);
	tmp[v_len - usr_len + home_len] = 0;

	log_debug("expanded '%s' -> '%s'", value, tmp);

	if (*dst_p)
		free(*dst_p);
	*dst_p = tmp;
	return true;
fail:
	log_error("cannot to expand filename: %s", value);
	return false;
}

bool cf_set_time_usec(void *dst, const char *value)
{
	usec_t *ptr = dst;
	*ptr = USEC * atof(value);
	return true;
}

bool cf_set_time_double(void *dst, const char *value)
{
	double *ptr = dst;
	*ptr = atof(value);
	return true;
}


