#! /bin/sh

set -e

top="$1"

# sanity check
test -n "$top" || {
  echo "usage: $0 USUAL_DIR SRC ..." >&2
  exit 1
}
test -f "$top/usual/base.h" || {
  echo "usage: $0 USUAL_DIR SRC ..." >&2
  exit 1
}

shift
test -n "$1" || exit 0

# return uniq module names, exclude already found ones
grep_usual() {
  excl="config"
  for m in $m_done; do
    excl="$excl|$m"
  done
  prog='
/^#include[ \t]*[<"]usual\/('"$excl"')[.]h/  { next; }
/^#include[ \t]*[<"]usual\// { p1 = index($0, "/"); p2 = index($0,"."); print substr($0, p1+1, p2-p1-1); }
'
  awk "$prog" "$@" | sort -u
}

# return module filename globs
make_pats() {
  for m in "$@"; do
    echo "$top/usual/$m*.[ch]"
  done
}

# loop over grep until all mods are found
m_done=""
m_tocheck=`grep_usual "$@"`
while test -n "$m_tocheck"; do
  m_done="$m_done $m_tocheck"
  pats=`make_pats $m_tocheck`
  m_tocheck=`grep_usual $pats`
done

# done
echo $m_done

