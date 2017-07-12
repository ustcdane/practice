#!/bin/bash

echo "rm cmake cache begin..."
rm -rf CMakeFiles
rm -rf CMakeCache.txt
rm -rf cmake_install.cmake
rm -rf expression_template
rm -rf naive_overloading
rm -rf test_crtp

echo "rm cmake cache end..."
