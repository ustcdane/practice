#include <zlib.h>
#include <iostream>
#include <string>

#define GZ_BUF_SIZE 1048576
// 使用C++和zlib解压缩.gz文件并读入内存
// g++ -o test gz_test.cpp -lz
bool gzLoad(char* gzfn, ::std::string &out) {
	//open .gz file
	gzFile gzfp = gzopen(gzfn,"rb");
	if(!gzfp) {
		return false;
	}

	//read and add it to out
	unsigned char buf[GZ_BUF_SIZE];
	int n;
	while( (n = gzread(gzfp,buf,GZ_BUF_SIZE)) > 0) {
		out.append((const char*)buf, n);
	}

	//close .gz file
	gzclose(gzfp);
	return true;
}

int main(int argc,char** argv) {
	if(argc!=2) {
		::std::cout<<"Usage: ./test xxx.gz"<<::std::endl;
		return -1;
	}

	::std::string out;
	if(gzLoad(argv[1],out)) {
		::std::cout<<out<<::std::endl;
	}
	else {
		::std::cout<<"gzLoad Error"<<::std::endl;
	}
	return 0;
}
