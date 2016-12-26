#!/bin/bash

str="hello exit 1"
if [[ $str =~ "exit" ]];then
	echo "yes $str"
else
	echo "No $str"
fi

if [[ `echo ${str} | grep "exit"` = 0  || $? -eq 0 ]];then
	echo "Y"
else
	echo "N"
fi

for i in $(seq 10)
	do
		echo $i
	done
for ((i=0 ; i<10; i++))
	do
		echo $i
done
a="aaaaaaaaaaaa"
if [ ${#a} -ne 2 ];then 
	echo "aaaa" 
fi

