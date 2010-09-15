
CFLAGS = -O -g
CPPFLAGS = -I../.. -DUSUAL -DUSE_INTERNAL_REGEX
LDFLAGS = -g
LIBS = ../libusual.a

all: testregex.usual testregex.libc

testregex.usual: testregex.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

testregex.o: testregex.c
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

testregex.libc: testregex.c
	$(CC)  $(CFLAGS) -o $@ $<


clean:
	rm -f testregex testregex.o testregex.usual testregex.libc

