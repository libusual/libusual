/*
 * ctype wrappers
 *
 * Copyright (c) 2011  Marko Kreen
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

/**
 * @file
 * ctype compat.
 *
 * Provides wrappers that make sure the functions work on 'char' values.
 *
 * @note
 * POSIX requires that these functions accept EOF/-1 in addition
 * to ordinary byte values.  That means when working on 'char',
 * the functions cannot differetiate between 0xFF and EOF.
 * As no code should give EOF to <ctype.h> functions and no code
 * should depend whether 0xFF is labeled ispunct() or not,
 * it seems no worthwhile to fix it.
 */

#ifndef _USUAL_CTYPE_H_
#define _USUAL_CTYPE_H_

#include <usual/base.h>

#include <ctype.h>

#ifndef HAVE_CTYPE_ON_CHAR

#define _WRAP_CTYPE_FN(name) \
	static inline int safe_ ## name (int c) { \
		return name((unsigned char)(c)); \
	}

_WRAP_CTYPE_FN(isalnum)
#undef isalnum
/** Safe isalnum */
#define isalnum(c) safe_isalnum(c)

_WRAP_CTYPE_FN(isalpha)
#undef isalpha
/** Safe isalpha */
#define isalpha(c) safe_isalpha(c)

_WRAP_CTYPE_FN(isascii)
#undef isascii
/** Safe isascii */
#define isascii(c) safe_isascii(c)

_WRAP_CTYPE_FN(isblank)
#undef isblank
/** Safe isblank */
#define isblank(c) safe_isblank(c)

_WRAP_CTYPE_FN(iscntrl)
#undef iscntrl
/** Safe iscntrl */
#define iscntrl(c) safe_iscntrl(c)

_WRAP_CTYPE_FN(isdigit)
#undef isdigit
/** Safe isdigit */
#define isdigit(c) safe_isdigit(c)

_WRAP_CTYPE_FN(isgraph)
#undef isgraph
/** Safe isgraph */
#define isgraph(c) safe_isgraph(c)

_WRAP_CTYPE_FN(islower)
#undef islower
/** Safe islower */
#define islower(c) safe_islower(c)

_WRAP_CTYPE_FN(isprint)
#undef isprint
/** Safe isprint */
#define isprint(c) safe_isprint(c)

_WRAP_CTYPE_FN(ispunct)
#undef ispunct
/** Safe ispunct */
#define ispunct(c) safe_ispunct(c)

_WRAP_CTYPE_FN(isspace)
#undef isspace
/** Safe isspace */
#define isspace(c) safe_isspace(c)

_WRAP_CTYPE_FN(isupper)
#undef isupper
/** Safe isupper */
#define isupper(c) safe_isupper(c)

_WRAP_CTYPE_FN(isxdigit)
#undef isxdigit
/** Safe isxdigit */
#define isxdigit(c) safe_isxdigit(c)

_WRAP_CTYPE_FN(tolower)
#undef tolower
/** Safe tolower */
#define tolower(c) safe_tolower(c)

_WRAP_CTYPE_FN(toupper)
#undef toupper
/** Safe toupper */
#define toupper(c) safe_toupper(c)

#undef _WRAP_CTYPE_FN

#endif /* HAVE_BROKEN_CTYPE */

#endif /* _USUAL_CTYPE_H_ */

