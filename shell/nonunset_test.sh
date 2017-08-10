#!/bin/bash

set -o nounset # raise unbound variable error
#WHATEVER=''
if [ ! -z ${WHATEVER} ];
	 then echo "yo"
fi

echo "whatever"
