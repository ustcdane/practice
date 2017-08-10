#!/bin/bash - 
#===============================================================================
#                                 DEFINITIONS
#===============================================================================
set -o nounset

sys_corpus='corpus.utf8.txt'

#===============================================================================
#                                 FUNCTIONS
#===============================================================================
function process(){
    local tmp="gbk.tmp"
	export LANG="zh_CN.GBK"
    # 0: dos2unix
    dos2unix $sys_corpus
	
    # 1: 转换字符编码、去掉拼音分隔符、去掉文件中添加的英文等
    iconv -f utf-8 -t gbk ${sys_corpus} | sed "s/'//g" | awk 'length($0)>1' | \
    sed '/[A-Z]/'d | awk '($1!~/[0-9]/){OFS = "\t"; print $2, $1, $3}' > $tmp
}


#===============================================================================
#                                 CALLS
#===============================================================================
l=`locale`
echo $l
process




#===============================================================================
#                                 REFRENCES
#===============================================================================
#  [ -a FILE ]  如果 FILE 存在则为真。  #{{{
#  [ -b FILE ]  如果 FILE 存在且是一个块特殊文件则为真。  
#  [ -c FILE ]  如果 FILE 存在且是一个字特殊文件则为真。  
#  [ -d FILE ]  如果 FILE 存在且是一个目录则为真。  
#  [ -e FILE ]  如果 FILE 存在则为真。  
#  [ -f FILE ]  如果 FILE 存在且是一个普通文件则为真。  
#  [ -g FILE ]  如果 FILE 存在且已经设置了SGID则为真。  
#  [ -h FILE ]  如果 FILE 存在且是一个符号连接则为真。  
#  [ -k FILE ]  如果 FILE 存在且已经设置了粘制位则为真。  
#  [ -p FILE ]  如果 FILE 存在且是一个名字管道(F如果O)则为真。  
#  [ -r FILE ]  如果 FILE 存在且是可读的则为真。  
#  [ -s FILE ]  如果 FILE 存在且大小不为0则为真。  
#  [ -t FD ]    如果文件描述符 FD 打开且指向一个终端则为真。  
#  [ -u FILE ]  如果 FILE 存在且设置了SUID (set user ID)则为真。  
#  [ -w FILE ]  如果 FILE 如果 FILE 存在且是可写的则为真。  
#  [ -x FILE ]  如果 FILE 存在且是可执行的则为真。  
#  [ -O FILE ]  如果 FILE 存在且属有效用户ID则为真。  
#  [ -G FILE ]  如果 FILE 存在且属有效用户组则为真。  
#  [ -L FILE ]  如果 FILE 存在且是一个符号连接则为真。  
#  [ -N FILE ]  如果 FILE 存在 and has been mod如果ied since it was last read则为真。  
#  [ -S FILE ]  如果 FILE 存在且是一个套接字则为真。 
#  
#  [ -z STRING ]  “STRING” 的长度为零则为真。  
#  [ -n STRING ] or [ STRING ]  “STRING” 的长度为非零 non-zero则为真。  
#  [ STRING1 == STRING2 ]  如果2个字符串相同。 “=” may be used instead of “==” for strict POSIX compliance则为真。  
#  [ STRING1 != STRING2 ]  如果字符串不相等则为真。 
#  [ STRING1 < STRING2 ]  如果 “STRING1” sorts before “STRING2” lexicographically in the current locale则为真。  
#  [ STRING1 > STRING2 ]  如果 “STRING1” sorts after “STRING2” lexicographically in the current locale则为真。  
#
#  [ ARG1 OP ARG2 ] “OP” is one of -eq, -ne, -lt, -le, -gt or -ge. “ARG1” and “ARG2” are integers}
#
#  var=$[$var op INT] 这个方法可以用来更新已有变量。#}}}

