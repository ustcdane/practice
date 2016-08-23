#include <zlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

#define GZ_LINE_BUF_SIZE 8192
// 使用C++和zlib解压缩.gz文件并读入内存
// g++ -o test gz_read_line_test.cpp -lz

// 按行打印
bool gzProcess(char* gzfn) {
	//open .gz file
	gzFile gzfp = gzopen(gzfn,"rb");
	if(!gzfp) {
		return false;
	}

	//read data
	char buf[GZ_LINE_BUF_SIZE];
	char *offset = buf;
	int line_num = 0;
	while( true ) {
		int err, len = sizeof(buf) - (offset - buf);
		if (len == 0) {
			printf("Buffer to small for input line lengths\n");
			return false;
		}
		len = gzread(gzfp, offset, len);
		std::cout<<"read size:"<<len<<std::endl;
		if(len == 0 ) break;
		if (len < 0) {
			printf("gz read error!\n");
			return false;
		}
		char *cur = buf;
		char *end = offset + len;
		// print each line
		for (char *eol; (cur < end) && (eol = std::find(cur, end, '\n')) < end; cur = eol + 1) {
			std::cout<<line_num++<<" : "<<std::string(cur, eol)<<std::endl;
		}
		offset = std::copy(cur, end, buf);
	}
	std::cout<<line_num++<<" : "<<std::string(buf, offset)<<std::endl;
	//close .gz file
	if(Z_OK != gzclose(gzfp)) {
			printf("gz file close failed!!\n");
	}
	return true;
}

int main(int argc,char** argv) {
	if(argc!=2) {
		std::cout<<"Usage: ./test xxx.gz"<<::std::endl;
		return -1;
	}

	if(gzProcess(argv[1])) {
		//::std::cout<<out<<::std::endl;
		std::cout<<"\nsuccess!\n";
	}
	else {
		std::cout<<"gzLoad Error"<<::std::endl;
	}
	return 0;
}
