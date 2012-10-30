
AM_CPPFLAGS = -I$(builddir) -I$(srcdir)

# main target
lib_LTLIBRARIES = libusual.la

# sources that are not always built
EXTRA_libusual_la_SOURCES = usual/pgsocket.h usual/pgsocket.c

# sources not in tar.gz
nodist_libusual_la_SOURCES = usual/config.h

# regular source files
libusual_la_SOURCES = usual/config.h.in \
	usual/aatree.h usual/aatree.c \
	usual/base.h usual/base.c usual/base_win32.h \
	usual/bits.h \
	usual/cbtree.h usual/cbtree.c \
	usual/cfparser.h usual/cfparser.c \
	usual/crc32.h usual/crc32.c \
	usual/ctype.h \
	usual/cxalloc.h usual/cxalloc.c \
	usual/cxextra.h usual/cxextra.c \
	usual/daemon.h usual/daemon.c \
	usual/endian.h \
	usual/err.h usual/err.c \
	usual/event.h usual/event.c \
	usual/fileutil.h usual/fileutil.c \
	usual/getopt.h usual/getopt.c \
	usual/hashtab-impl.h \
	usual/heap.h usual/heap.c \
	usual/hmac.h usual/hmac.c \
	usual/list.h usual/list.c \
	usual/logging.h usual/logging.c \
	usual/lookup3.h usual/lookup3.c \
	usual/mbuf.h usual/mbuf.c \
	usual/md5.h usual/md5.c \
	usual/mdict.h usual/mdict.c \
	usual/mempool.h usual/mempool.c \
	usual/misc.h \
	usual/netdb.h usual/netdb.c \
	usual/pgutil.h usual/pgutil.c usual/pgutil_kwlookup.h \
	usual/pthread.h usual/pthread.c \
	usual/regex.h usual/regex.c \
	usual/safeio.h usual/safeio.c \
	usual/sha1.h usual/sha1.c \
	usual/shlist.h \
	usual/signal.h usual/signal.c \
	usual/slab.h usual/slab.c \
	usual/socket.h usual/socket.c usual/socket_ntop.c usual/socket_pton.c usual/socket_win32.h \
	usual/statlist.h \
	usual/string.h usual/string.c \
	usual/strpool.h usual/strpool.c \
	usual/time.h usual/time.c \
	usual/utf8.h usual/utf8.c

# we want to filter headers, so cannot use usual install method via _HEADERS
USUAL_HEADERS = $(filter %.h,$(libusual_la_SOURCES) $(nodist_libusual_la_SOURCES))

# define aclocal destination
aclocaldir = ${datarootdir}/aclocal
AM_DESTINATIONS = aclocal

# other files
dist_pkgdata_SCRIPTS = find_modules.sh
dist_pkgdata_DATA = Setup.mk
dist_aclocal_DATA = m4/usual.m4 m4/antimake.m4

# test program for link-test
noinst_PROGRAMS = test/compile
test_compile_SOURCES = test/compile.c
test_compile_LDADD = libusual.la

# extra clean files
DISTCLEANFILES = config.log build.mk config.status libtool config.mak
MAINTAINERCLEANFILES = build.mk.in configure install-sh ltmain.sh config.sub config.guess

# files for .tgz that are not mentioned in sources
EXTRA_DIST = $(MAINTAINERCLEANFILES)

# we dont build test subdir by default, but want to include in .tgz
DIST_SUBDIRS = test

# non-recursive subdir
EMBED_SUBDIRS = mk

#
# Launch Antimake
#
include build.mk

# filter headers when installing
install-local:
	@$(MKDIR_P) $(DESTDIR)$(includedir)/usual
	@for hdr in $(USUAL_HEADERS); do \
		echo Filtering $$hdr; \
		$(SED) -f mk/safe-headers.sed $$hdr \
		> $(DESTDIR)$(includedir)/usual/`basename $$hdr`; \
	done

# Give proper error message
build.mk:
	@echo "Please run ./configure first"
	@exit 1

%.pc: %.pc.in config.status
	./config.status --file $@

# run sparse over code
sparse: config.mak
	REAL_CC="$(CC)" \
	$(MAKE) clean libusual.a CC="cgcc -Wsparse-all -Wno-transparent-union"

# generate api documentation
dox:
	rm -rf doc/html/mk
	#rm -rf mk/temos/html
	doxygen doc/Doxyfile
	$(MAKE) -C mk/temos html
	cp -rp mk/temos/html doc/html/mk

#
# rest is for pgutil_kwlookup generation
#

PG_CONFIG ?= pg_config
KWLIST = $(shell $(PG_CONFIG) --includedir-server)/parser/kwlist.h
GPERF = gperf -m5

# requires 8.4+
kws:
	@test -f "$(KWLIST)" || { echo "kwlist.h not found"; exit 1; }
	grep '^PG_KEYWORD' "$(KWLIST)" \
	| grep -v UNRESERVED \
	| sed 's/.*"\(.*\)",.*, *\(.*\)[)].*/\1/' \
	>> usual/pgutil_kwlookup.gp

kwh:
	$(GPERF) usual/pgutil_kwlookup.g \
	| sed '/^#line/d' \
	> usual/pgutil_kwlookup.h

sizes: all
	size `find .objs -name '.libs' -prune -o -name '*.o' -print | sort`

%.s: %.c
	$(CC) -S $(DEFS) $(CFLAGS) $(CPPFLAGS) -I. $< -o - | cleanasm > $@

