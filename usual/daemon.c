/*
 * Daemonization & pidfile handling.
 *
 * Copyright (c) 2007-2009  Marko Kreen, Skype Technologies OÜ
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


#include <usual/daemon.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

#include <usual/logging.h>

/*
 * pidfile management.
 */

static char *g_pidfile;

static void remove_pidfile(void)
{
	if (!g_pidfile)
		return;
	unlink(g_pidfile);
	free(g_pidfile);
	g_pidfile = NULL;
}

static void check_pidfile(const char *pidfile)
{
	char buf[128 + 1];
	struct stat st;
	pid_t pid = 0;
	int fd, res;

	if (!pidfile || !pidfile[0])
		return;

	/* check if pidfile exists */
	if (stat(pidfile, &st) < 0) {
		if (errno != ENOENT)
			fatal_perror("stat");
		return;
	}

	/* read old pid */
	fd = open(pidfile, O_RDONLY);
	if (fd < 0)
		goto locked_pidfile;
	res = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (res <= 0)
		goto locked_pidfile;

	/* parse pid */
	buf[res] = 0;
	pid = atol(buf);
	if (pid <= 0)
		goto locked_pidfile;

	/* check if running */
	if (kill(pid, 0) >= 0)
		goto locked_pidfile;
	if (errno != ESRCH)
		goto locked_pidfile;

	/* seems the pidfile is not in use */
	log_info("Stale pidfile, removing");
	unlink(pidfile);
	return;

locked_pidfile:
	fatal("pidfile exists, another instance running?");
}

static void write_pidfile(const char *pidfile)
{
	char buf[64];
	pid_t pid;
	int res, fd, len;

	if (!pidfile || !pidfile[0])
		return;

	if (g_pidfile)
		free(g_pidfile);
	g_pidfile = strdup(pidfile);
	if (!g_pidfile)
		fatal_perror("cannot alloc pidfile");

	pid = getpid();
	snprintf(buf, sizeof(buf), "%u\n", (unsigned)pid);

	fd = open(pidfile, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
		fatal_perror("%s", pidfile);
	len = strlen(buf);
loop:
	res = write(fd, buf, len);
	if (res < 0) {
		if (errno == EINTR)
			goto loop;
		fatal_perror("%s", pidfile);
	} else if (res < len) {
		len -= res;
		goto loop;
	}
	close(fd);

	/* only remove when we have it actually written */
	atexit(remove_pidfile);
}

/*
 * Function: daemonize
 *
 * Handle pidfile and daemonization.
 *
 * If pidfile is given, check if old process is running.
 *
 * If going background is required, require non-empty pidfile
 * and logfile.  Then fork to background and write pidfile.
 */
void daemonize(const char *pidfile, bool go_background)
{
	int pid, fd;

	if (pidfile && pidfile[0]) {
		check_pidfile(pidfile);
		if (!go_background)
			write_pidfile(pidfile);
	} else if (go_background)
		fatal("daemon needs pidfile configured");

	if (!go_background)
		return;

	if (!cf_logfile && !cf_syslog_ident)
		fatal("daemon needs logging configured");

	/* send stdin, stdout, stderr to /dev/null */
	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		fatal_perror("/dev/null");
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	/* fork new process */
	pid = fork();
	if (pid < 0)
		fatal_perror("fork");
	if (pid > 0)
		_exit(0);

	/* create new session */
	pid = setsid();
	if (pid < 0)
		fatal_perror("setsid");

	/* fork again to avoid being session leader */
	pid = fork();
	if (pid < 0)
		fatal_perror("fork");
	if (pid > 0)
		_exit(0);

	write_pidfile(pidfile);
}

