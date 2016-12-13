#!/bin/sh
# http://www.swig.org/Doc1.3/Python.html
SWIG_DIR="/search/odin/tools/swig-3.0.10"
SWIGEXE=$SWIG_DIR/swig
SWIG_LIB_DIR=$SWIG_DIR/Lib
MODULE_NAME="sayHi"
INTERFACE=./sayHi.i
#LIBS=-lm
#build
#env SWIG_LIB="$SWIG_LIB_DIR"

# target language is python
$SWIGEXE -python -c++ $INTERFACE

#编译，生成so文件 g++

#need Pyhont.h so yum install python-dev 
# will generate sayHi.o sayHi_wrap.o
g++ -c -fPIC  sayHi.cpp "$MODULE_NAME"_wrap.cxx    -I/usr/include/python2.7 

# -o  _"$MODULE_NAME".so 注意前面的_
g++ -shared  "$MODULE_NAME".o "$MODULE_NAME"_wrap.o -o  _"$MODULE_NAME".so
