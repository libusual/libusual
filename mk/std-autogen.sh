#! /bin/sh

USUAL_DIR="$1"
test -n "${USUAL_DIR}" || USUAL_DIR="."

test -f "${USUAL_DIR}/m4/usual.m4" || {
  echo usage: $0 USUAL_DIR
  exit 1
}

# 
# workaround for libtoolize bug - it does not update
# the file if they dont exist
rm -f config.guess config.sub install-sh ltmain.sh libtool
if libtoolize --help | grep "[-][-]install" > /dev/null; then
  libtoolize -i -q -f
else
  libtoolize
fi

# drop ltmain.sh if libtool is not used
grep -qE 'LT_INIT|LIBTOOL' configure.ac || rm -f ltmain.sh

# Now generate configure & config.h
aclocal -I${USUAL_DIR}/m4
autoheader
autoconf

# workaround for old autotools that dont provide install-sh
test -f install-sh || cp -p ${USUAL_DIR}/mk/install-sh .

# clean junk
rm -rf autom4te.* aclocal*

