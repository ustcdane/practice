#!/bin/sh

PROJNAME=http_test
MAINDIR=`pwd`

mkdir -p gopath/src/$PROJNAME/module
rm -f $PROJNAME

#sed ...
sed -e "s/\$PROJNAME/$PROJNAME/" httpTest.go > httpTest.go.sed
# cp mv ...
mv httpTest.go.sed gopath/src/$PROJNAME/httpTest.go

#cp module.h module.i gopath/src/$PROJNAME/module
#cd gopath/src/$PROJNAME/module
#env SWIG_LIB=/search/odin/tools/swig-3.0.10/Lib  swig -go -c++ -cgo -intgosize 64  -o module_wrap.cxx module.i

#github.com/valyala/fasthttp need set gopath
GOPATH=$MAINDIR/gopath
export GOPATH;
echo $GOPATH

CGO_CPPFLAGS=""
export CGO_CPPFLAGS;
echo $CGO_CPPFLAGS
CGO_CFLAGS=""
export CGO_CFLAGS;
echo $CGO_CFLAGS

CGO_CXXFLAGS="-std=c++11 -I/usr/local/include  -I. "
export CGO_CXXFLAGS;
echo $CGO_CXXFLAGS

#CGO_LDFLAGS="-Wl,-rpath,./libs/  -L$MAINDIR/libs/ -lswc"
export CGO_LDFLAGS;
echo $CGO_LDFLAGS

cd $MAINDIR/gopath/src/$PROJNAME

go get -v #获得相应的依赖包
go build -v

cp $GOPATH/bin/$PROJNAME $MAINDIR
