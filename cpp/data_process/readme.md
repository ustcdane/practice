c++ threadPool process data.
Use  c++ cppUtils test.  
</br>
1. TO split data
</br>
./split_weekly_data.sh want.txt 500 > log.txt 2>&1 &
</br>
2. TO process data </br>
./generateFourFive unigram.txt input output 4 > log.txt 2>&1 &
</br>
3. TO merge data </br>
./merge_weekly_data.sh output gram_4.txt > log.txt 2>&1 &
</br>
