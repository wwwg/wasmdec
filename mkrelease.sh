#!/bin/bash

# simple script to export files to the release/ directory

if [[ $EUID -ne 0 ]]; then
   echo "you must be root" 
   exit 1
fi

mkdir -p release/

make binaryen
make default

cp wasmdec release/
cp external/binaryen/lib/libbinaryen.so release/

tar -czvf release.tar.gz release/