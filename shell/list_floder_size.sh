#!/bin/bash
#罗列当前目录下文件及文件夹大小
for i in `ls .`
do
	if [ -d ./$i ];then
		du -sh ./$i
	else
		ls -lh $i
	fi
done
