
-include config.mak

# config
MKAR = $(AR) rcs
CFLAGS += $(WFLAGS)
CPPFLAGS = $(USUAL_CPPFLAGS)

# sources
USUAL_DIR = .
USUAL_OBJDIR = obj
USUAL_MODULES = $(filter-out pgsocket, $(subst .h,, $(notdir $(wildcard $(USUAL_DIR)/usual/*.h))))
include $(USUAL_DIR)/Setup.mk

# tgz generation
FULL = libusual-$(shell date +%Y-%m-%d)
DIRS = usual m4 test
IGNORE = usual/config.h test/config.h test/test_config.h
FILES = $(filter-out $(IGNORE), $(wildcard usual/*.[ch] test/*.[ch])) \
	m4/usual.m4 configure configure.ac COPYRIGHT \
	Makefile README config.mak.in Setup.mk \
	find_modules.sh test/force_compat.sed test/Makefile

# pgutil_kwlookup generation
PG_CONFIG ?= pg_config
KWLIST = $(shell $(PG_CONFIG) --includedir-server)/parser/kwlist.h
GPERF = gperf -m5

# full path for files
srcs = $(USUAL_SRCS)
hdrs = $(USUAL_HDRS)
objs = $(USUAL_OBJS)

# Quiet by default, 'make V=1' shows commands
V=0
ifeq ($(V), 0)
Q = @
E = @echo
else
Q =
E = @true
endif

# rules follow

all: info libusual.a obj/testcompile

libusual.a: $(objs)
	$(E) "	AR" $@
	$(Q) $(MKAR) $@ $(objs)

$(USUAL_OBJDIR)/%.o: $(USUAL_DIR)/usual/%.c config.mak $(hdrs)
	@mkdir -p $(USUAL_OBJDIR)
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $<

$(USUAL_OBJDIR)/%.s: $(USUAL_DIR)/usual/%.c config.mak $(hdrs)
	@mkdir -p $(USUAL_OBJDIR)
	$(E) "	CC -S" $<
	$(Q) $(CC) -S -fverbose-asm -o - $(DEFS) $(CPPFLAGS) $(CFLAGS) $< \
	| cleanasm > $@

obj/testcompile: test/compile.c libusual.a config.mak $(hdrs)
	$(E) "	CHECK" $<
	$(Q) $(CC) -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $< $(USUAL_LDFLAGS) $(USUAL_LIBS) $(LIBS)

test/test_string: test/test_string.c libusual.a config.mak $(hdrs)
	$(E) "	TEST" $@
	$(Q) $(CC) -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $< $(USUAL_LDFLAGS) $(USUAL_LIBS) $(LIBS)
	$(Q) ./$@

check: config.mak
	mkdir -p test/usual
	sed -f test/compat.sed usual/config.h > test/usual/config.h
	make clean
	make CPPFLAGS="-I./test $(CPPFLAGS)" all
	make CPPFLAGS="-I./test $(CPPFLAGS)" test/test_string

clean:
	rm -f libusual.a obj/*.[os] obj/test* aclocal* config.log
	rm -rf autom4te*
	rm -f usual/pgutil_kwlookup.h.gp

distclean: clean
	rm -f config.mak usual/config.h config.status

realclean:
	rm -f usual/pgutil_kwlookup.h

boot:
	rm -rf usual/config.*
	aclocal -I ./m4
	autoheader
	autoconf
	rm -rf aclocal* autom4te.*

#config.mak:
#	@echo "Config out-of-date, please run ./configure again"
#	@exit 1

#usual/config.h:
#	@echo "Please run ./configure first"
#	@exit 1

# run sparse over code
sparse: config.mak
	REAL_CC="$(CC)" \
	$(MAKE) clean libusual.a CC="cgcc -Wsparse-all -Wno-transparent-union"

asms = $(objs:.o=.s)
asm: $(asms)

dbg: flags
	@echo srcs=$(srcs)
	@echo objs=$(objs)
	@echo hdrs=$(hdrs)

flags:
	@echo DEFS=$(DEFS)
	@echo CFLAGS=$(CFLAGS)
	@echo CPPFLAGS=$(CPPFLAGS)

info:
	@echo CC: $(CC) $(DEFS) $(CPPFLAGS) $(CFLAGS)
	@echo LD: $(LD) $(USUAL_LDFLAGS) $(USUAL_LIBS) $(LIBS)

.PHONY: flags dbg info

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

tgz: config.mak $(DISTFILES)
	# create tarfile
	rm -rf $(FULL) $(FULL).tgz usual/config.h
	mkdir $(FULL)
	(for f in $(DIRS) $(FILES); do echo $$f; done) | cpio -pm $(FULL)
	tar czf $(FULL).tgz $(FULL)
	rm -rf $(FULL)

dox:
	doxygen doc/Doxyfile

