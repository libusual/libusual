

#vpath %.mak ..
#vpath %.mk ..
#vpath %.c ..
#vpath %.h ..

override CPPFLAGS = -I. -I..
override USUAL_DIR = ..

override DEFS = -DUSUAL_TEST_CONFIG
OBJS = test_string.o test_crypto.o test_aatree.o test_heap.o \
       test_common.o test_list.o tinytest.o test_cbtree.o \
       test_utf8.o test_strpool.o test_pgutil.o test_regex.o \
       test_cxalloc.o

test-all: regtest

include ../Makefile

%.o: %.c $(hdrs)
	@mkdir -p $(USUAL_OBJDIR)
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $<


test_config.h: ../usual/config.h force_compat.sed
	sed -f force_compat.sed $< > $@

#libusual.a: test_config.h

regtest: test_config.h libusual.a $(OBJS)
	$(E) "	LD" $@
	$(Q) $(CC) -o $@ $(OBJS) -L. -lusual

clean: clean-test

clean-test:
	rm -f libusual.a obj/* *.o regtest
	rm -f config.test usual/config.h test_config.h

config.mak: ../config.mak
	cp ../config.mak .
