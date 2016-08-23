#!/bin/sh

function merge() {
	if [ $# != 2 ];then
		echo "params error!"
		echo "use: out_dir out_file_name"
		exit 1
	fi

	if [ ! -d $1 ];then
		echo "out_dir path does not exist!"
		exit 1
	fi
	
	input_dir=$1
	out_file=$2
	list_file=`ls $1`
	
	# 计算总的文件行数
	g_nums=0
	for v in ${list_file[@]}
	do
		echo "${input_dir}/${v}"
		lines=`wc -l "${input_dir}/${v}" | awk '{print $1}'`
		let g_nums="$g_nums+$lines"
	done
	echo "Total lines: $g_nums"

	i=0
	local arr
	max_num=4097 # 默认概率对数的最大值 4096 先默认为0
	while [ $i -lt $max_num ] # for ((i=0;i<4097;i++)) is also ok
	do
		arr[$i]=0
		#echo $i
		let i++
	done
	# 存在这样的文件则置为1
	for v in ${list_file[@]}
	do
		arr[${v%%.*}]=1
	done

	echo "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
	
	echo $g_nums > $out_file
	i=0
	while [ $i -lt ${#arr[@]} ] 
	do
		if [ 1 -eq ${arr[$i]} ];then
			echo "merge file ${i}.out"
			cat "${input_dir}/$i.out" >> $out_file
		fi
		let i++
	done
}

merge $1 $2
