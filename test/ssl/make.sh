#! /bin/sh

rm -rf TestCA1 TestCA2

./newca.sh TestCA1 C=QQ O=Org1 CN="TestCA1"
./newsite.sh TestCA1 example.com C=AA O=Org1 L=city1 OU=none
./newsite.sh TestCA1 client1 C=BB O=Org1 L=city2 OU=none
./newsite.sh TestCA1 random1 C=CC O=Org1 L=city3 OU=none

./newca.sh TestCA2 C=ZZ O=Org1 CN="TestCA2"
./newsite.sh TestCA2 sample.org C=DD O=Org2 L=city4 OU=none
./newsite.sh TestCA2 client2 C=EE O=Org2 L=city5 OU=none
./newsite.sh TestCA2 random2 C=FF O=Org2 L=city6 OU=none

