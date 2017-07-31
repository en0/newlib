#!/usr/bin/env bash

which i686-rpos-cc >/dev/null
if [ $? != 0 ]; then
    echo OS Toolchain is not in path. Cannot build.
    exit 1
fi

DESTDIR="$(readlink -f $PWD/../../../)"

rm -rf newlib-build
mkdir -p newlib-build
cd newlib-build

../configure --prefix=/usr --target=i686-rpos
make all
make DESTDIR=$DESTDIR install

cd -
