#!/bin/bash

echo "make clean"

rm -rf CMakeFiles
rm -rf CMakeCache.txt
rm -rf cmake_install.cmake

cmake ..
make

#删除cmake产生的无用文件
rm -rf CMakeFiles
rm -rf CMakeCache.txt
rm -rf cmake_install.cmake
