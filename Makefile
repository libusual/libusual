
-include config.mak

# config
MKAR = $(AR) rcs
CFLAGS += $(WFLAGS)
CPPFLAGS = $(USUAL_CPPFLAGS)

# sources
USUAL_DIR = .
USUAL_OBJDIR = obj
USUAL_MODULES = $(subst .h,, $(notdir $(wildcard usual/*.h)))
include $(USUAL_DIR)/Setup.mk

# extra warning flags
WFLAGS = -Wextra -Wno-unused-parameter -Wno-missing-field-initializers \
	 -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement \
	 -Wold-style-definition -Wstrict-prototypes -Wundef -Wformat -Wnonnull \
	 -Wstrict-overflow

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

obj/%.o: usual/%.c config.mak $(hdrs)
	@mkdir -p obj
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $<

obj/%.s: usual/%.c config.mak $(hdrs)
	@mkdir -p obj
	$(E) "	CC -S" $<
	$(Q) $(CC) -S -fverbose-asm -o - $(DEFS) $(CPPFLAGS) $(CFLAGS) $< \
	| cleanasm > $@

obj/testcompile: test/compile.c libusual.a config.mak $(hdrs)
	$(E) "	CHECK" $<
	$(Q) $(CC) -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $< $(USUAL_LDFLAGS) $(USUAL_LIBS) $(LIBS)

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

config.mak: usual/config.h
	@echo "Config out-of-date, please run ./configure again"
	@exit 1

usual/config.h:
	@echo "Please run ./configure first"
	@exit 1

asms = $(objs:.o=.s)
asm: $(asms)

