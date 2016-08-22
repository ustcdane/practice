#!/bin/sh
# ./split_weekly_data.sh ../finalbigresult/weekly_four.txt 1840
function init() {
	if [ $# != 2 ];then
		echo "params error!!!"
		echo "Use: $0 input_dir output_dir"
		exit 1
	fi
	echo -e "input_dir: $1\noutput_dir: $2"
	
	if [ -d $1 ];then
		echo "$1 exists"
		rm -f $1/*
	else
		echo "$1  dose not exists!!!"
		exit 1
	fi
	
	if [ -d $2 ];then
		echo "$2 exists"
		rm -f $2/*
	else
		echo "$2  dose not exists, mkdir $2"
		mkdir $2
	fi
}

function process() {
	
	if [ $# != 4 ];then
		echo "params error!!!"
		echo "Use: $0 data_file 1540(threshold) input_dir output_dir"
		exit 1
	fi
	
	echo -e "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	echo -e "data file:$1\nthreshold:$2\ninput_dir:$3\noutput_dir:$4"
	echo -e "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	
	if [ -f $1 ];then
		echo "$1 exists"
	else
		echo "$1  dose not exists!!!"
		exit 1
	fi
	
	init $3 $4
	if [ $? != 0 ];then
		echo "init Failed!!"
		exit 1
	else
		echo "init success!"
	fi
	echo "-------------------------------------"
	#gawk -v input_dir="$3" -F '\t' '{if(NF == 2) { print input_dir; print $0 >> input_dir"/"$2".txt";print input_dir;}} ' $1
	`LC_ALL=C`
	gawk -v threshold="$2" -v input_dir="$3" -F '\t' '{if(NF == 2 && $2<=threshold) { print $0 >> input_dir"/"$2".txt";}}' $1
	#gawk -v input_dir="$3"  '{print NF;if(NF == 2) { print $0 >> input_dir"//"$2".txt";}} ' $1

}



if [ $# != 2 ];then
	echo "params error!!!"
	echo "Use: $0 data_file 1540(threshold)"
	exit 1
fi

#process ../finalbigresult/weekly_four.txt 1840
process $1 $2 "input" "output"
if [ $? != 0 ];then
	echo "split data Failed!!"
	exit 1
else
	echo "init success!"
fi
