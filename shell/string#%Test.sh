#!/bin/sh

str="http://www.12306.cn/mormhweb/otn"
#${varible#*string} form left to right, del the string first occur(from begin to string)

echo ${str#*//} #result is:www.12306.cn/mormhweb/

#${varible##*string} form left to right, del the string last occur(from begin to string)
echo ${str##*/} #result is:otn

#${varible%string*} form right left, del the string fisrt occur(from end to string)
echo ${str%/*} #http://www.12306.cn/mormhweb

#${varible%string*} form right left, del the string last occur(from end to string)
echo ${str%%/*} # http:
