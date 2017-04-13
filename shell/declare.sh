#!/bin/bash

function de(){
	declare -a arr
	for ((i=0; i<5; ++i)); do
		arr[$i]="$i"
	done
	echo "arr[*]:" ${arr[*]}
}
de
