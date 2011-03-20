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
  excl="nonex"
  for m in $m_done; do
    excl="$excl|$m"
  done
  awk "
/^#include[ \t]*[<\"]usual\\/($excl)[.]h/  { next; }
/^#include[ \t]*[<\"]usual\\//             { split(\$0, tmp, \"[./]\"); print tmp[2]; }
" "$@" \
  | sort -u
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

