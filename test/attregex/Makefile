
#CC = i586-mingw32msvc-gcc
CFLAGS = -O -g
CPPFLAGS = -I../..
DEFS = -DUSUAL -DUSE_INTERNAL_REGEX
LDFLAGS = -g
LIBS = ../libusual_compat.a

all: testregex.usual testregex.libc

testregex.usual: testregex.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

testregex.o: testregex.c
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

testregex.libc: testregex.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<


clean:
	rm -f testregex testregex.o testregex.usual testregex.libc

