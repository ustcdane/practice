#!/bin/bash

#ymd="20170512"

if [ -z "${ymd: }" ];then # string length is 0
	echo $ymd "is empty"
else
	echo "$ymd not empty"
fi
