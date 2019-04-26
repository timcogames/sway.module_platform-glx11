#!/bin/sh

if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
	CMAKE_URL=https://cmake.org/files/v3.14/cmake-${CMAKE_VERSION}-Linux-x86_64.sh
	mkdir -p ${CMAKE_ROOT}
	pushd ${CMAKE_ROOT}
	wget ${CMAKE_URL}
	chmod +x cmake-*-Linux-x86_64.sh
	./cmake-*-Linux-x86_64.sh --exclude-subdir --skip-license
	export PATH="${PWD}/bin:$PATH"
	popd
else
	if ! brew ls --version cmake &>/dev/null; then brew update; brew install cmake; fi
fi
