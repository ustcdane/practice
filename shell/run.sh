#!/bin/sh

#source "/search/bin/hcommon.sh"


#-D mapred.map.tasks=6 \
#-D mapred.reduce.tasks=2 \
#-file "reducer.py" \
#-reducer "python reducer.py" \

input="/user/ime/DBG/gz/20160[1-4]/*/*.gz" 
output="/user/ime/wangdan/DBG_Corpus/asso_gc_data"
hadoop fs -rmr "$output"

hadoop jar "/usr/lib/hadoop/contrib/streaming/hadoop-streaming-0.20.2-cdh3u4.jar" \
-D mapred.job.name="Daniel PC DBG asso gc data Stat" \
-D stream.num.map.output.key.fields=3 \
-D mapred.text.key.partitioner.options='-k1,1' \
-D mapred.output.key.comparator.class=org.apache.hadoop.mapred.lib.KeyFieldBasedComparator \
-D mapred.text.key.comparator.options='-k1,1 -k2,2' \
-D mapred.output.compress=true \
-D mapred.output.compression.codec=org.apache.hadoop.io.compress.GzipCodec \
-D mapred.reduce.tasks=1 \
-partitioner org.apache.hadoop.mapred.lib.KeyFieldBasedPartitioner \
-file "mapper" \
-mapper "mapper"  \
-reducer "cat" \
-input "$input" \
-output "$output"
