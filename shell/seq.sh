#!/bin/bash

# seq.sh a b c d e

echo "seq test:[1-5]"
for i in $(seq 1 5)
do
echo $i
done

echo "param num is $#:"

for i in $(seq 1 $#)
do
	eval j=\$$i
	echo "($"$i"):" $j
done

shift 3

echo "after shift 3:"
echo "param num is $#:"

for i in $(seq 1 $#)
do
	eval j=\$$i
	echo "($"$i"):" $j
done
