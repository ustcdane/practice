#!/bin/sh
# expand grams by ngrams_ex.sh result




# 2_ex.txt
#2:1
#3:4

#bigram.txt
#2 1 259
#3 2 281

#use:
# sh make_expand_corpus.sh corpus_20161226/ corpus_20161228

if [ 2 -ne $# ];then
	echo "param error!"
	echo "sh $0 corpus_origin corpus_out"
	exit 1
fi

corpus_origin=$1
corpus_out=$2

sh memory_free.sh

arr=("" "" "bigram.txt" "trigram.txt" "gram_4.txt" "gram_5.txt")

# make_corpus 2 2_ex.txt corpus_in/bigram.txt corpus_out/bigram.txt
function make_corpus() {
	#@param1 ngram
	if [ $# -ne 4 ];then
		echo "$0 n ex_gram input out"
		return 1
	fi
	nGram=$1
	ex_gram=$2
	input_file=$3
	output_file=$4

	if [ ! -f $ex_gram ];then
		echo "$ex_gram ex_gram file does't a file"
		return 1
	fi

	if [ ! -f $input_file ];then
		echo "$input_file gram file does't a file"
		return 1
	fi
	
	rm -f $output_file
	
	echo "$FUNCNAME $nGram $input_file $output_file"
	
	# 获得扩展gram的行数
	ex_gram_num=`wc -l $ex_gram 2>&1 | awk '{print(int($1))}'`
	 # 待扩展的gram的行数, 第一行即为此gram的有效行数
	input_file_num=`head -1 $input_file | awk '{print(int($1))}'`

	 # 扩展后总的行数
	let sum=$ex_gram_num+$input_file_num
	# grams file µÄÆ¬¶ÎÊý
	let segs_num=$nGram+1
	# grams file的最大词频
	freq=`tail -1 $input_file | awk -v segs_num="$segs_num" -F '\t' '{print(int($segs_num))}'`

	echo "$ex_gram has $ex_gram_num lines"
	echo "$input_file has $input_file_num lines"
	echo "Total lines will be: $ex_gram_num+$input_file_num=$sum"
	echo "$input_file max freq is $freq"
	# 新扩展的ngram词频为最大词频+2
	let max_freq=$freq+2

	#echo $sum
	# merge 
	echo "merge $nGram-gram"
	echo "PID of $nGram running $FUNCNAME: $BASHPID"
	
	echo "$sum" > $output_file
	awk -v segs_num=$segs_num -F '\t' '{if(NF == segs_num)print $0}' $input_file >> $output_file
	awk -v max_freq="$max_freq" -F ':' '{res="";for(x=1;x<=NF;x++){res=res""$x"\t";};res=res""max_freq; print res}' $ex_gram >> $output_file
}

#################################### main #####################

num=2
while [ $num -lt 6 ]
do
	#echo ${arr[$num]}
	if [ -f $corpus_origin/${arr[$num]} ];then
		echo "process $corpus_origin/${arr[$num]}"
		make_corpus $num ${num}_ex.txt $corpus_origin/${arr[$num]} $corpus_out/${arr[$num]} 2>&1 &
	else
		continue
	fi
	#echo "process.."
#	./add_grams add_ngram/${num}.txt $num $corpus/${arr[$num]} >  ${num}_ex.txt  2>&1 & 
	let num++
done
