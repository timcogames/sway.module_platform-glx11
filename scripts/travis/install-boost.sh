#!/bin/sh

if [[ -d "$BOOST_ROOT/lib" ]] ; then
	echo "Using cached boost at $BOOST_ROOT"
	exit
fi

BOOST_URL="https://dl.bintray.com/boostorg/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION//\./_}.tar.gz"
BOOST_LIBS="filesystem"
BOOST_BUILD_TYPE="architecture=x86 address-model=32_64 variant=release threading=multi link=static stage"
mkdir -p ${BOOST_ROOT}
pushd ${BOOST_ROOT}
wget --quiet -O - ${BOOST_URL} | tar --strip-components=1 -xz
./bootstrap.sh --with-libraries=${BOOST_LIBS}
sudo ./b2 ${BOOST_BUILD_TYPE}
popd
