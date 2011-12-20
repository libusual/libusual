#! /bin/sh

# autogen for non-automake trees
#
# - it installs files: config.sub, config.guess, install-sh
# - it installs ltmain.sh, if LT_INIT or *LIBTOOL macro is used
#

USUAL_DIR="$1"
test -n "${USUAL_DIR}" || USUAL_DIR="."

test -f "${USUAL_DIR}/m4/usual.m4" || {
  echo usage: $0 USUAL_DIR
  exit 1
}

# 
# Workarounds for libtoolize randomness - it does not update
# the files if they exist, except it requires install-sh.
#
rm -f config.guess config.sub install-sh ltmain.sh libtool
cp -p ${USUAL_DIR}/mk/install-sh .
if libtoolize --help | grep "[-][-]install" > /dev/null; then
  libtoolize -i -f -q
else
  libtoolize
fi

# drop ltmain.sh if libtool is not used
grep -E 'LT_INIT|LIBTOOL' configure.ac > /dev/null || rm -f ltmain.sh

# Now generate configure & config.h
aclocal -I ${USUAL_DIR}/m4

grep AC_CONFIG_HEADER configure.ac > /dev/null && autoheader

autoconf

# clean junk
rm -rf autom4te.* aclocal*

