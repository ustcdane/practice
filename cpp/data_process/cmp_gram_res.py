#!/bin/env python

f1 = open("gram_4.txt", "r")
f2 = open("../finalbigresult/gram_4.txt", "r")

i=0

while True:
	line1 = f1.readline()
	line1 = line1.strip()
	line2 = f2.readline()
	line2 = line2.strip()
	if not line1 or not line2:
		break
	i+=1
	if line1 != line2:
		print i,line1,line2

f1.close()
f2.close()



