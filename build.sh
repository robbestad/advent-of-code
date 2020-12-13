#!/bin/sh
basedir=`pwd`
cd build
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..
make
cd ..
${basedir}/build/aoc
