#!/usr/bin/env bash

if [ $# -ne 1 ];then
	echo "$0 param error! please input input_file"
	exit 1
fi
bi_file=$1
awk '{if(NF==7)printf("%s %s %s %s %s %s %s\n", $2,$1,$3,$4,$5,$6,$7);}' $bi_file > uni.txt
awk '{if(NF==11)printf("%s %s %s %s %s %s %s %s %s %s %s\n", $2,$1,$4,$3,$5,$6,$7,$8,$9,$10,$11);}' $bi_file > bi.txt
