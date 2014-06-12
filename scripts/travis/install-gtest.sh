#!/usr/bin/env bash

svn checkout http://googletest.googlecode.com/svn/trunk/ gtest

cd gtest
mkdir build
cd build
cmake .. && make
cd ../..

exit 0
