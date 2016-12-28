#!/bin/bash
#http://blog.csdn.net/firefoxbug/article/details/7426109

TestID()
{
	echo "in function use \$\$ : $$"
	echo "\$BASHPID inside of subshell = $BASHPID"
	sleep 20
}

TestID &
TestID &

echo "\$! outside of subshell : $! "
echo "\$\$ outside of subshell : $$ "
echo "\$BASHPID outside of subshell = $BASHPID"

sleep 1

