/*
 * File access utils.
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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <usual/fileutil.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Load text file into C string.
 */

char *load_file(const char *fn)
{
	struct stat st;
	char *buf = NULL;
	int res;
	FILE *f;

	res = stat(fn, &st);
	if (res < 0)
		return NULL;

	buf = malloc(st.st_size + 1);
	if (!buf)
		return NULL;

	f = fopen(fn, "r");
	if (!f)
		return NULL;

	if ((res = fread(buf, 1, st.st_size, f)) < 0) {
		fclose(f);
		return NULL;
	}

	fclose(f);
	buf[st.st_size] = 0;

	return buf;
}

/*
 * Read file line-by-line, call user func on each.
 */

bool foreach_line(const char *fn, procline_cb proc_line, void *arg)
{
	char *ln = NULL;
	size_t len = 0;
	ssize_t res;
	FILE *f = fopen(fn, "rb");
	if (!f)
		return false;
	while (1) {
		res = getline(&ln, &len, f);
		if (res < 0)
			break;
		proc_line(arg, ln, res);
	}
	fclose(f);
	free(ln);
	return true;
}

/*
 * Find file size.
 */

ssize_t file_size(const char *fn)
{
	struct stat st;
	if (stat(fn, &st) < 0)
		return -1;
	return st.st_size;
}

/*
 * Map a file into mem.
 */

int map_file(struct MappedFile *m, const char *fname, int rw)
{
	struct stat st;
	m->fd = open(fname, rw ? O_RDWR : O_RDONLY);
	if (m->fd < 0)
		return -1;
	if (fstat(m->fd, &st) < 0) {
		close(m->fd);
		return -1;
	}
	m->len = st.st_size;
	m->ptr = mmap(NULL, m->len, PROT_READ | (rw ? PROT_WRITE : 0),
		      MAP_SHARED, m->fd, 0);
	if (m->ptr == MAP_FAILED) {
		close(m->fd);
		return -1;
	}
	return 0;
}

void unmap_file(struct MappedFile *m)
{
	munmap(m->ptr, m->len);
	close(m->fd);
	m->ptr = NULL;
	m->fd = 0;
}

