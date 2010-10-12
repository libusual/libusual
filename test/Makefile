

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
       test_cxalloc.o test_bits.o test_base.o test_netdb.o

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

regtest.compat: ../usual/config.h force_compat.sed
	sed -f force_compat.sed $< > test_config.h
	make regtest
	mv regtest regtest.compat
	mv libusual.a libusual_compat.a
	rm test_config.h

regtest.system: ../usual/config.h
	cp $< test_config.h
	make regtest
	mv regtest regtest.system
	mv libusual.a libusual_system.a
	rm test_config.h

test: regtest.compat regtest.system
	./regtest.compat
	./regtest.system

