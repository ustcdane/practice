#!/bin/bash

s='ha¹þ¹þa'

#locale

# if locale is LANG=en_US length will be 7
#if locale is LANG=zh_CN.GB18030 length will be 5
echo $s | awk '{print $1, length($1)}'

# length always be 5
echo $s | LANG="zh_CN.GBK" awk  '{print $1, length($1)}'
