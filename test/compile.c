#include <usual/aatree.h>
#include <usual/base.h>
#include <usual/cbtree.h>
#include <usual/cfparser.h>
#include <usual/crc32.h>
#include <usual/daemon.h>
#include <usual/endian.h>
#include <usual/err.h>
#include <usual/event.h>
#include <usual/fileutil.h>
#include <usual/hashtab-impl.h>
#include <usual/heap.h>
#include <usual/list.h>
#include <usual/logging.h>
#include <usual/lookup3.h>
#include <usual/mbuf.h>
#include <usual/md5.h>
#include <usual/misc.h>
//#include <usual/pgsocket.h>
#include <usual/safeio.h>
#include <usual/shlist.h>
#include <usual/signal.h>
#include <usual/slab.h>
#include <usual/socket.h>
#include <usual/statlist.h>
#include <usual/string.h>
#include <usual/time.h>
#include <usual/utf8.h>

static inline bool heap_is_better(const void *a, const void *b)
{
	return 1;
}

int main(void)
{
	struct AATree aatree;
	struct CBTree *cbtree;
	struct md5_ctx md5;
	char buf[128];

	aatree_init(&aatree, NULL, NULL);
	cbtree = cbtree_create(NULL, NULL, NULL, USUAL_ALLOC);
	daemonize(NULL, NULL);
	hash_lookup3("foo", 3);
	if (!event_init())
		log_debug("test");
	if (!parse_ini_file("foo", NULL, NULL))
		log_debug("test");
	log_stats("1");
	file_size("foo");
	md5_reset(&md5);
	strlcpy(buf, "foo", sizeof(buf));
	printf("xmalloc: %p\n", xmalloc(128));
	if (0) die("0");
	return 0;
}

