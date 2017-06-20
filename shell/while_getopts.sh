#!/bin/bash - 
#===============================================================================
#   shell's while and getopts usage
#===============================================================================

set -o nounset                              # Treat unset variables as an error


# sh while_getopts.sh -T 3 o.txt a.txt b.txt
function usage() {
    echo "$0 [options] local_output input*"
    echo "options: -[hm]"
    echo "-h    print this help information"
    echo "-m    name of use-provided mapper script"
    echo "-T n  set frequence threshold to n, such as -T 1600:1580 or -T 1600"
}

if [ $# -lt 4 ]; then
    usage >&1;
    exit 1;
fi

threshold=2

while getopts 'hm:T:' opt; do
    case "$opt" in
        h) usage; exit;     ;;
        m) mapper=$OPTARG;  ;;
        T) threshold="$OPTARG"; ;;
        ?) usage; exit 1;   ;;
    esac
done
echo "threshold is:$threshold"
shift $(($OPTIND - 1))

output="$1"
shift
input="$@"

defmap=`mktemp mapper.XXXXXXXXXX`
cat > "$defmap" <<-'EOF'
#!/usr/bin/env python 
import sys
for line in sys.stdin:
    try:
        line = line.strip()
        (key, value) = line.split('\t')
        if not len(value):
            continue
        print "%s\t%s" % (key, value)
    except:
        print >>sys.stderr, "invalid line:%s" % line
EOF
chmod +x "$defmap"

trap "rm -f $defmap;" EXIT TERM KILL ABRT INT

mapper="${mapper:-$defmap}"

rm $output
touch $output

echo "input: $input"
echo "defmap: $defmap"
echo "mapper: $mapper"

for i in $input
do
    if [ -f $i ];then
        cat $i | python $mapper >> $output
    fi
done

[ $? -eq 0 ] || echo "$0: fail to run!" && exit 1
