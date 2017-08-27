#!/bin/bash

# This shell is used to explain how cython setup.py works.
#

if [ $# -ne 1 ];then
	echo "parameters error!!"
	echo "usage: $0 XXX { The name of XXX.pyx, exclude .pyx}"
	echo "e.g.:sh build.sh cython_evaluate"
	exit 1
fi

name=$1

python_inc=`ls /usr/include/ | grep python`

echo "python headers:$python_inc"

#  Will create a ${name}.c file
cython ${name}.pyx

# Compile the object file
gcc -c -fPIC -I/usr/include/${python_inc}/ ${name}.c

# Link it into a shared library
gcc -shared ${name}.o -o ${name}.so
