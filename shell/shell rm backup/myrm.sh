#!/bin/bash


###trash目录define
realrm="/bin/rm"
TRASH=/search/wangdan
trash_dir=$TRASH/.myrmtrash/
trash_log=$TRASH/.myrmtrash.log
###判断trash目录是否存在，不存在则创建
if [ ! -d $trash_dir ] ;then
	mkdir -v $trash_dir
fi



###动态修改用户shell中的alias配置
os_type=`uname`
shell_path=$SHELL
shell_type=`echo $SHELL|awk -F/ '{print $NF}'`
alias_file=~/.${shell_type}rc
alias_rm=`cat $alias_file|grep ^"alias rm="`
return_value=$?
#echo return_value: $return_value
#echo alias_rm: $alias_rm
###如果不存在rm alias，则生成
[ ! -f /bin/myrm.sh ] && \cp -f ./myrm.sh /bin/;
if [[ $return_value -ne 0 ]] ;then
	echo 'first time to run myrm'
	echo "alias rm=/bin/myrm.sh" >>$alias_file && source $alias_file
###如果存在rm alias，且不是指向rmtrash的，则注释掉，区分linux 和mac
elif [[ "$alias_rm" != "alias rm=/bin/myrm.sh" ]];then
	echo already has alias rm,and must commit out
	if [[ $os_type == Darwin ]];then
		sed -i .bak 's/^alias\ rm=/#alias\ rm=/g' $alias_file && \
		echo "alias rm=/bin/myrm.sh" >>$alias_file && \
		source $alias_file
	elif [[ $os_type == Linux ]];then
		sed -i.bak 's/^alias\ rm=/#alias\ rm=/g' $alias_file && \
		echo "alias rm=/bin/myrm.sh" >>$alias_file && \
		source $alias_file
	fi
fi





myrm() { 
	D=$trash_dir/$(date +%Y%m%d%H%M%S); 
	mkdir -p $D; 
	mv "$@" $D && echo "moved to $D ok" >> $trash_log;
	tail -1 $trash_log
}

if [ $# -ne 0 ];then
	#echo $@
	myrm $@
else
	echo "please input file or dir"
fi


