#!/usr/bin/env bash

#which i686-rpos-cc >/dev/null
#if [ $? != 0 ]; then
    #echo OS Toolchain is not in path. Cannot build.
    #exit 1
#fi
#DESTDIR="$(readlink -f $PWD/../../../)"
##../configure --prefix=/usr --target=i686-rpos

abort() {
    MESSAGE=$1
    EXITCODE=$2
    if [[ -z "$EXITCODE" ]]
    then
        EXITCODE=1
    fi

    printf "ERROR: %s\n" "${MESSAGE}" 1>&2
    exit $EXITCODE
}

require_env() {
    [[ -z "$2" ]] && \
        abort "\$$1 is not set. Please source the desired environment." 1
}

require_env "SYSROOT" "${SYSROOT}"
require_env "PREFIX" "${PREFIX}"
require_env "TARGET" "${TARGET}"
require_env "PATH" "${PATH}"

rm -rf newlib-build
mkdir -p newlib-build
cd newlib-build

../configure \
    --prefix=${PREFIX} \
    --with-build-sysroot=${SYSROOT} \
    --target=${TARGET} && make all && make install
