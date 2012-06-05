#! /bin/sh

# autogen for non-automake trees
#
# - it installs files: config.sub, config.guess, install-sh
# - it installs ltmain.sh, if LT_INIT or *LIBTOOL macro is used
#

set -e

USUAL_DIR="$1"
test -n "${USUAL_DIR}" || USUAL_DIR="."

test -f "${USUAL_DIR}/m4/usual.m4" || {
  echo usage: $0 USUAL_DIR
  exit 1
}

# default programs
ACLOCAL=${ACLOCAL:-aclocal}
AUTOCONF=${AUTOCONF:-autoconf}
AUTOHEADER=${AUTOHEADER:-autoheader}

# detect first glibtoolize then libtoolize
if test "x$LIBTOOLIZE" = "x"; then
  LIBTOOLIZE=glibtoolize
  which $LIBTOOLIZE >/dev/null 2>&1 \
    || LIBTOOLIZE=libtoolize
fi

# 
# Workarounds for libtoolize randomness - it does not update
# the files if they exist, except it requires install-sh.
#
rm -f config.guess config.sub install-sh ltmain.sh libtool
cp -p ${USUAL_DIR}/mk/install-sh .
if ${LIBTOOLIZE} --help | grep "[-][-]install" > /dev/null; then
  ${LIBTOOLIZE} -i -f -q -c
else
  ${LIBTOOLIZE} -c
fi

# drop ltmain.sh if libtool is not used
grep -E 'LT_INIT|LIBTOOL' configure.ac > /dev/null \
  || rm -f ltmain.sh

# Now generate configure & config.h
${ACLOCAL} -I ${USUAL_DIR}/m4

grep AC_CONFIG_HEADER configure.ac > /dev/null \
  && ${AUTOHEADER}

${AUTOCONF}

# clean junk
rm -rf autom4te.* aclocal*

