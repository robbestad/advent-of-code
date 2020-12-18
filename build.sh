#!/bin/sh
basedir=`pwd`
cd build || exit
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ -c -Q -O3 ..
make
cd ..
${basedir}/build/aoc
