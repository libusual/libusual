# config
DEFS = -DCASSERT
CC = gcc
MKAR = ar rcs
CFLAGS = -O2 -g -Wall $(WFLAGS)
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

obj/%.o: usual/%.c $(hdrs)
	@mkdir -p obj
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $<

obj/testcompile: test/compile.c libusual.a $(hdrs)
	$(E) "	CHECK" $<
	$(Q) $(CC) -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $< $(USUAL_LDFLAGS) $(USUAL_LIBS)

clean:
	rm -f libusual.a obj/*.o obj/test*

