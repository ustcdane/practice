#!/bin/sh
PROJNAME=goTest
MAINDIR=`pwd`

SWIG_DIR="/search/odin/tools/swig-3.0.10"
SWIGEXE=$SWIG_DIR/swig
SWIG_LIB_DIR=$SWIG_DIR/Lib
MODULE_NAME="sayHi"

GOEXE=$GOROOT/bin/go
GOPATH=$MAINDIR/gopath;
export GOPATH;
echo $GOPATH

#LIBS=-lm
#build
#env SWIG_LIB="$SWIG_LIB_DIR"

rm -rf gopath/*
mkdir -p gopath/src/$PROJNAME/module
#rm -f $PROJNAME
rm -fr gopath/src/$PROJNAME/module/*

sed -e "s/\$PROJNAME/$PROJNAME/" runme.go > runme.go.sed
mv runme.go.sed gopath/src/$PROJNAME/runme.go

cp "$MODULE_NAME".h  "$MODULE_NAME".cpp "$MODULE_NAME".i  gopath/src/$PROJNAME/module/

cd $MAINDIR/gopath/src/$PROJNAME/module/

CGO_CXXFLAGS="-std=c++11 -I/usr/local/include  -I. "
export CGO_CXXFLAGS;
echo $CGO_CXXFLAGS

echo "Building ..."
swig -go -c++ -cgo -intgosize 64  -o "$MODULE_NAME"_wrap.cxx  "$MODULE_NAME".i
go install

cd $MAINDIR/gopath/src/$PROJNAME/
go build runme.go
cp runme $MAINDIR

cd $MAINDIR
./runme
