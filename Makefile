
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

all: libusual.a obj/testcompile

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

distclean: clean
	rm -f config.mak usual/config.h

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
check: config.mak
	REAL_CC="$(CC)" \
	$(MAKE) clean libusual.a CC="cgcc -Wsparse-all"

asms = $(objs:.o=.s)
asm: $(asms)

dbg:
	@echo srcs=$(srcs)
	@echo objs=$(objs)
	@echo hdrs=$(hdrs)
	@echo CPPFLAGS=$(CPPFLAGS)

