#!/bin/bash

le="aa"
echo ${#le}
#  ${value//pattern/string} pattern replaced by string
temp=20161205,20161114,20161010,20160929
arr=(${temp//,/ })
echo ${#arr[@]}

for i in ${arr[@]}
do
	echo $i
done

types=(a b c d)
type_num="${#types[*]}"
echo $type
echo $type_num
echo ${#types[@]}
