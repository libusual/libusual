

#vpath %.mak ..
#vpath %.mk ..
#vpath %.c ..
#vpath %.h ..

override CPPFLAGS = -I. -I..
override USUAL_DIR = ..

override DEFS = -DUSUAL_TEST_CONFIG
SRCS = test_string.c test_crypto.c test_aatree.c test_heap.c \
       test_common.c test_list.c tinytest.c test_cbtree.c \
       test_utf8.c test_strpool.c test_pgutil.c test_regex.c \
       test_cxalloc.c test_bits.c test_base.c test_netdb.c \
       test_cfparser.c
OBJS = $(SRCS:.c=.o)

test-all: regtest.compat

include ../Makefile

hdrs += test_config.h

%.o: %.c $(hdrs)
	@mkdir -p $(USUAL_OBJDIR)
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $(DEFS) $(CPPFLAGS) $(CFLAGS) $<


regtest: libusual.a $(OBJS)
	$(E) "	LD" $@
	$(Q) $(CC) -o $@ $(OBJS) -L. -lusual

clean: clean-test

clean-test:
	rm -f libusual.a obj/* *.o regtest
	rm -f config.test usual/config.h test_config.h
	rm -f regtest.compat regtest.system
	rm -f libusual_compat.a libusual_system.a

config.mak: ../config.mak
	cp ../config.mak .

regtest.compat: ../usual/config.h force_compat.sed $(SRCS)
	sed -f force_compat.sed $< > test_config.h
	make regtest
	mv regtest regtest.compat
	mv libusual.a libusual_compat.a
	rm test_config.h

regtest.system: ../usual/config.h $(SRCS)
	cp $< test_config.h
	make regtest
	mv regtest regtest.system
	mv libusual.a libusual_system.a
	rm test_config.h

test: regtest.compat regtest.system
	./regtest.compat
	./regtest.system

