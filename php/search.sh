#!/usr/bin/env bash
if [ $# -ne 3 ];then
	echo "param error!"
	exit 1
fi

left=$1
right=$2
cur_dir=$(cd `dirname $0`; pwd)
#echo $cur_dir
# 文件目录
bigram_dir=$cur_dir/$3
#echo $bigram_dir
#不存在相关版本的目录则报错
if [ ! -d $bigram_dir ];then
	echo "version:$3 not existing!"
	exit 1
fi
cd $bigram_dir


function draw_table()
{
	if [ $# -ne 1 ];then
		exit 1
	fi
	IFS=' '
	array=($1)
	num=${#array[@]}   
	if [ $num = 0 ];then
		echo "</br>"
		return;
	fi

	row="<tr>"
	for s in ${array[@]}
	do
		row="$row""<td>""$s""</td>"
	done
	row="$row""</tr>"
	echo $row
}

echo "<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\" width=\"90%\">"

#画表 一元信息
echo "<tr><td><strong>unigram info:</strong></tr></td>"
echo "<tr><td>"
echo "<table cellspacing=\"0\" cellpadding=\"0\" border=\"1\" bordercolor=\"\#000000\" width=\"60%\"  style=\"BORDER-COLLAPSE: collapse\" >"

L=`grep ^"$left"[a-z] uni.txt`
R=`grep ^"$right"[a-z] uni.txt`
#uni_msg="word  id  unigram  backoff  pattern  lid  rid"
uni_msg="元词  元词id  一元词频  回退词频  模式  半命中拆分左id  半命中拆分右id"
draw_table "$uni_msg"

if [[ -z "$L" || -z "$R" ]];then
	echo $L
	echo $R
	draw_table "$L"
	draw_table "$R"
	echo "</table>"
	echo "<tr><td>left or right unigram not existing!</tr></td>"
	echo "</table>"
	exit  1
fi

bi=`grep ^"$left"[a-z] bi.txt| grep $right |awk '{printf("%s\#",$0);}'`
#bi=`grep ^"$left"[a-z] bi.txt| grep $right`
if [ -z "$bi" ];then
	#echo -e $uni_msg
	draw_table "$L"
	draw_table "$R"
	echo "</table>"
	echo "<tr><td>bigram not existing!</tr></td>"
	echo "</table>"
	exit 1
fi

draw_table "$L"
draw_table "$R"
echo "</table>"
echo "</tr></td>" # 一元表格绘制结束


# 画表 二元信息
echo "<tr><td><strong>bigram info:</strong></tr></td>"
echo "<tr><td>"
#bi_msg="wordl  idl  wordr  idr  gramvalue   bitinfo cainfo  canfilt rank_in_py  merge_word  origin_gram"
bi_msg="左元  左元id  右元  右元id  压缩二元值   bitinfo 调频信息  canfilt 同音下排序  左右元合并  原始二元值"
echo "<table  cellspacing=\"0\" cellpadding=\"0\" border=\"1\" bordercolor=\"\#000000\" width=\"70%\"  style=\"BORDER-COLLAPSE: collapse\" >"
draw_table "$bi_msg"

ifs=$IFS
IFS='\#'
array=($bi)
for line in ${array[@]}
do
	draw_table "$line"
done
IFS=$ifs

echo "</table>"
echo "</tr></td>" # 二元信息表格绘制结束

echo "</table>"


