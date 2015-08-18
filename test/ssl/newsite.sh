#! /bin/sh

# new server key + cert under some CA

test -n "$2" || {
  echo "usage: $0 <CaName> <SiteDns>"
  exit 1
}

test -f "$1/ca.key" || {
  echo "CA $1 does not exist"
  exit 1
}

days=10240

. ./lib.sh

CaName="$1"
DstName="$2"
shift 2

ser=`cat $CaName/serial`

pfx=$CaName/sites/${ser}-$DstName

if test "$KTYPE" = "rsa"; then
  run openssl genrsa -out "$pfx.key" 2048
else
  run openssl ecparam -genkey -name secp384r1 -out $pfx.key
fi

# cert reqs
run_req -new -key "$pfx.key" -out "$pfx.csr" -- CN="$DstName" "$@"

# accept certs
run_ca -days $days -policy pol-server -in "$pfx.csr" -out "$pfx.crt"

