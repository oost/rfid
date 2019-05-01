#!/bin/sh
# Copyright (c) 2019 Oscar Ostlund (soscar.ostlund@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

# exit on firts error
set -e

mkdir -p build
cd build

# Generate a Makefile for GCC (or Clang, depanding on CC/CXX envvar)
cmake -DCMAKE_BUILD_TYPE=Debug -DMFRC522_USE_GCOV=OFF -DMFRC522_BUILD_EXAMPLES=ON -DMFRC522_BUILD_TESTS=ON -DMFRC522_RUN_CPPCHECK=ON ..

# Build (ie 'make')
cmake --build .

# Build and run unit-tests (ie 'make test')
ctest --output-on-failure