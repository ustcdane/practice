#!/bin/sh
# 把servertest_python 拷贝到不同的机器进行分布式的压力测试
# au.txt为多台机器的ip
v=`awk '{print $1}' au.txt`

for i in $v;
do
	echo $i
	ssh root@$i "cd /search/user/servertest_python;  ./get_load_test.py" 
done

