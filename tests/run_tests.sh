#!/usr/bin/env bash
set -euo pipefail

# Simple test runner for the unit test source in tests/
CXX=${CXX:-clang++}
CXXFLAGS=${CXXFLAGS:-"-std=c++14 -O0 -ggdb -I./src"}

mkdir -p ./bin
echo "Compiling test_two_spheres..."
$CXX $CXXFLAGS -o ./bin/test_two_spheres tests/test_two_spheres.cpp
echo "Running tests..."
./bin/test_two_spheres
