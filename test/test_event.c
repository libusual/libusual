#include <usual/event.h>
#include <usual/socket.h>

#include <string.h>

#include "test_common.h"

static int ev_count;

static void bumper(int fd, short flags, void *arg)
{
	int res;
	int *other = arg;
	char buf[10];

	ev_count++;

	res = recv(fd, buf, 10, 0);
	if (res != 1) {
		fprintf(stderr, "recv: %s\n", strerror(errno));
		event_loopbreak();
	}

	buf[0]++;
	if (buf[0] > 'z') {
		event_loopbreak();
	} else {
		send(*other, buf, 1, 0);
	}
}

static void test_event(void *z)
{
	struct event_base *base = NULL;
	int spair[2];
	struct event ev[2];

	base = event_init();

	tt_assert(socketpair(AF_UNIX, SOCK_STREAM, 0, spair) == 0);
	tt_assert(socket_setup(spair[0], true));
	tt_assert(socket_setup(spair[1], true));

	event_set(&ev[0], spair[0], EV_READ | EV_PERSIST, bumper, &spair[1]);
	tt_assert(event_add(&ev[0], NULL) == 0);
	event_set(&ev[1], spair[1], EV_READ | EV_PERSIST, bumper, &spair[0]);
	tt_assert(event_add(&ev[1], NULL) == 0);

	tt_assert(send(spair[0], "0", 1, 0) == 1);

	tt_assert(event_loop(0) == 0);

	event_base_free(base);

	int_check(ev_count, 75);
end:;
}

struct testcase_t event_tests[] = {
	{ "event", test_event },
	END_OF_TESTCASES
};

