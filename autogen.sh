#! /bin/sh

# get install-sh, config.*
rm -f config.sub config.guess install-sh ltmain.sh
libtoolize --install --copy
# ignore libtool itself
rm -f ltmain.sh

rm -f usual/config.* configure
aclocal -I ./m4
autoheader
autoconf
rm -rf autom4te*

