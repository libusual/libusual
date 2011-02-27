

SRCS = test_string.c test_crypto.c test_aatree.c test_heap.c \
       test_common.c test_list.c tinytest.c test_cbtree.c \
       test_utf8.c test_strpool.c test_pgutil.c test_regex.c \
       test_cxalloc.c test_bits.c test_base.c test_netdb.c \
       test_cfparser.c test_endian.c test_hashtab.c test_mdict.c \
       test_shlist.c test_time.c test_hashing.c test_fileutil.c \
       test_socket.c test_getopt.c test_ctype.c

OBJS = $(addprefix obj/, $(SRCS:.c=.o))
HDRS = test_common.h test_config.h tinytest.h tinytest_macros.h
LIBS =

USUAL_DIR = ..
USUAL_OBJDIR = obj
USUAL_LOCAL_SRCS = $(SRCS) $(HDRS)
include $(USUAL_DIR)/Setup.mk
include ../config.mak

DEFS += -DUSUAL_TEST_CONFIG
CPPFLAGS += -I.. -I.

hdrs = $(HDRS) $(USUAL_HDRS)
objs = $(OBJS) $(USUAL_OBJS)

.SUFFIXES:

# Quiet by default, 'make V=1' shows commands
V=0
ifeq ($(V), 0)
Q = @
E = @echo
else
Q = 
E = @true
endif

all: regtest

obj/%.o: %.c $(hdrs)
	@mkdir -p obj
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $< $(DEFS) $(CFLAGS) $(CPPFLAGS) $(WFLAGS)

obj/%.o: $(USUAL_DIR)/usual/%.c $(hdrs)
	@mkdir -p obj
	$(E) "	CC" $<
	$(Q) $(CC) -c -o $@ $< $(DEFS) $(CFLAGS) $(CPPFLAGS) $(WFLAGS)

regtest: $(objs)
	$(E) "	LD" $@
	$(Q) $(CC) -o $@ $(LDFLAGS) $(objs) $(LIBS)

clean:
	rm -f libusual.a obj/* *.o regtest *.gcov
	rm -f config.test usual/config.h test_config.h
	rm -f regtest.compat regtest.system
	rm -f libusual_compat.a libusual_system.a

config.mak: ../config.mak
	cp ../config.mak .

test_config.h: ../usual/config.h force_compat.sed
	$(E) "	GEN-COMPAT" $<
	$(Q) sed -f force_compat.sed $< > test_config.h

sys: ../usual/config.h
	rm -f test_config.h
	cp ../usual/config.h test_config.h
	make

test: regtest
	./regtest

vcheck: regtest
	valgrind --leak-check=full ./regtest

BADGC = ../usual/base.c ../usual/signal.c
gc:
	make clean all CC="$(CC) -fprofile-arcs -ftest-coverage"
	./regtest
	gcov -f -o obj $(SRCS) $(filter-out $(BADGC), $(USUAL_SRCS)) > gc.log

