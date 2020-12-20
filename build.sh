#!/bin/sh
basedir=`pwd`
cmake -VCPKG_FEATURE_FLAGS \
	-DCMAKE_C_COMPILER=gcc \
	-DCMAKE_CXX_COMPILER=/usr/bin/g++ \
	-c -Q -O3 \
	-B build \
	-S -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
	.
cd build || exit
make
cd ..
${basedir}/build/aoc
