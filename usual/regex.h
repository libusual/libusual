/*
 * Small POSIX-only regex engine.
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

#ifndef _USUAL_REGEX_H_
#define _USUAL_REGEX_H_

#include <usual/base.h>

#if !defined(USE_INTERNAL_REGEX) && defined(HAVE_REGEX_H) && defined(HAVE_REGCOMP)
#define USE_SYSTEM_REGEX
#endif


#ifdef USE_SYSTEM_REGEX
#include <regex.h>
#else

/*
 * uRegex defines
 */

/* flags to regcomp() */
#define REG_EXTENDED	(1 << 0)
#define REG_ICASE	(1 << 1)
#define REG_NOSUB	(1 << 2)
#define REG_NEWLINE	(1 << 3)

/* flags to regexec() */
#define REG_NOTBOL	(1 << 4)
#define REG_NOTEOL	(1 << 5)

/* error codes */
#define REG_NOMATCH	1
#define REG_BADBR	2
#define REG_BADPAT	3
#define REG_BADRPT	4
#define REG_EBRACE	5
#define REG_EBRACK	6
#define REG_ECOLLATE	7
#define REG_ECTYPE	8
#define REG_EEND	9
#define REG_EESCAPE	10
#define REG_EPAREN	11
#define REG_ERANGE	12
#define REG_ESIZE	13
#define REG_ESPACE	14
#define REG_ESUBREG	15

/* max count user can enter via {} */
#undef RE_DUP_MAX
#define RE_DUP_MAX	0x7ffe

/*
 * Local flags to regcomp()
 */

/* allow \b\B\d\D\s\S\w\W\/ */
#define REG_RELAXED_SYNTAX	(1 << 14)

/* dont permute groups in attempt to get longest match */
#define REG_RELAXED_MATCHING	(1 << 15)

/* turn both on */
#define REG_RELAXED		(REG_RELAXED_SYNTAX | REG_RELAXED_MATCHING)

/* turn them permanently on */
#ifdef USUAL_RELAXED_REGEX
#undef REG_EXTENDED
#define REG_EXTENDED (1 | REG_RELAXED)
#endif

/* compiled regex */
typedef struct {
	int re_nsub;
	void *internal;
} regex_t;

/* match location */
typedef long regoff_t;
typedef struct {
	regoff_t rm_so;
	regoff_t rm_eo;
} regmatch_t;

/* avoid name conflicts */
#define regcomp(a,b,c) usual_regcomp(a,b,c)
#define regexec(a,b,c,d,e) usual_regexec(a,b,c,d,e)
#define regerror(a,b,c,d) usual_regerror(a,b,c,d)
#define regfree(a) usual_regfree(a)

/* public functions */
int regcomp(regex_t *rx, const char *re, int flags);
int regexec(const regex_t *rx, const char *str, size_t nmatch, regmatch_t pmatch[], int eflags);
size_t regerror(int err, const regex_t *rx, char *dst, size_t dstlen);
void regfree(regex_t *rx);

#endif /* !USE_SYSTEM_REGEX */

#endif /* _USUAL_REGEX_H_ */

