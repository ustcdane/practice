#!/bin/bash - 
#===============================================================================
#                                 DEFINITIONS
#===============================================================================
set -o nounset

runner="Daniel"
category="phone"
scheduler="ime"
h_input="/user/ime/wangdan/phone/bigram/test/"
h_output="/user/ime/wangdan/phone/bigram/test/merge.release"
h_output_debug="/user/ime/wangdan/phone/bigram/test/merge.debug"

#===============================================================================
#                                 MERGE BIGRAM
#===============================================================================
function merge(){
	local pigscript="merge_bigram.pig"
    echo " " > $pigscript

    #----------------------
    #   Global Setting
    #----------------------
    echo "SET default_parallel 1; " >> $pigscript
    echo "SET pig.noSplitCombination true;" >> $pigscript
    echo "SET job.name '${category}_merge_bigram:${runner}';" >> $pigscript
    echo "SET mapred.fairscheduler.pool ${scheduler}; " >> $pigscript

    #----------------------
    #   Merge Statement
    #----------------------
    # phone qq data etc.
	local key_list=(cell qq)
    local coe_list=(0.8 0.3) 

	local merge_str="merge = cogroup "
	for key in ${key_list[@]}
    do
        echo "${key} = load '${h_input}/${key}' as (key1:bytearray, key2:bytearray, tf:double, df:double);" >> "$pigscript"
		merge_str="${merge_str} ${key} by (key1, key2),"
	done
	echo "${merge_str%,};" >> "$pigscript"

    #----------------------
    #   Release Statement
    #----------------------
	local each_str="foreach merge generate flatten(group)"
	local sum_str_tf=""
	local sum_str_df=""
	# for normalization
	local sum_coe=""

    for ((i=0; i<${#key_list[@]}; i++))
    do
        key=${key_list[$i]}
        coe=${coe_list[$i]}
		sum_str_tf="${sum_str_tf}+${coe}*SUM((IsEmpty(${key})?{(0.0)}:${key}.tf))"
		sum_str_df="${sum_str_df}+${coe}*SUM((IsEmpty(${key})?{(0.0)}:${key}.df))"
		sum_coe="${sum_coe}+${coe}*SUM((IsEmpty(${key})?{(0.0)}:{(1.0)}))"
	done
	
	# non normalization
	#local each_str="${each_str}, ${sum_str_tf#+}, ${sum_str_df#+}"
	
	#normalization
	local each_str="${each_str}, (float)(${sum_str_tf#+})/(${sum_coe#+}), (float)(${sum_str_df#+})/(${sum_coe#+})"
    
	echo "release = ${each_str};" >> $pigscript
    echo "store release into '${h_output}';" >> $pigscript
	
    #----------------------
    #   Debug Statement
    #----------------------
    for ((i=0; i<${#key_list[@]}; i++))
    do
        key=${key_list[$i]}
        coe=${coe_list[$i]}
		each_str="${each_str}, '${key}','${coe}', flatten((IsEmpty(${key})?{(0.0,0.0)}:${key}.(tf,df)))"
	done
	echo "debug = ${each_str};" >> "$pigscript"
	echo "store debug into '${h_output_debug}';" >> "$pigscript"

    #----------------------
    #   Run PigScript
    #----------------------
    hadoop fs -rmr $h_output
    hadoop fs -rmr $h_output_debug
	pig -f $pigscript
	[ $? -eq 0 ] || errexit "merge process failed!"
#	rm "$pigscript"
}

#===============================================================================
#                                 CALL HERE
#===============================================================================
merge

