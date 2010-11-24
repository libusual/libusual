

include ../../config.mak

DEFS += -DUSUAL -DUSE_INTERNAL_REGEX
CPPFLAGS += -I../..
OBJS = testregex.o regex.o mempool.o

all: testregex.usual testregex.libc

testregex.usual: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

testregex.o: testregex.c
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

regex.o: ../../usual/regex.c ../../usual/regex.h
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

mempool.o: ../../usual/mempool.c ../../usual/mempool.h
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

testregex.libc: testregex.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<


clean:
	rm -f testregex *.o testregex.usual testregex.libc

