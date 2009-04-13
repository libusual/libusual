#include <usual/aatree.h>
#include <usual/alloc.h>
#include <usual/base.h>
#include <usual/cbtree.h>
#include <usual/cfparser.h>
#include <usual/daemon.h>
#include <usual/event.h>
#include <usual/fileutil.h>
#include <usual/list.h>
#include <usual/logging.h>
#include <usual/lookup3.h>
#include <usual/md5.h>
#include <usual/safeio.h>
#include <usual/slab.h>
#include <usual/socket.h>
#include <usual/statlist.h>
#include <usual/string.h>
#include <usual/time.h>

int main(void)
{
	struct AATree aatree;
	struct CBTree *cbtree;
	struct md5_ctx md5;
	char buf[128];

	aatree_init(&aatree, NULL, NULL);
	cbtree = cbtree_create(NULL);
	daemonize(NULL, NULL);
	hash_lookup3("foo", 3);
	if (!event_init())
		log_debug("test");
	if (!parse_ini_file("foo", NULL, NULL))
		log_debug("test");
	file_size("foo");
	md5_reset(&md5);
	strlcpy(buf, "foo", sizeof(buf));
	return 0;
}

