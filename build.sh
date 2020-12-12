#!/bin/sh
basedir=`pwd`
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ --build build
cd build
make
cd ..
${basedir}/build/aoc
