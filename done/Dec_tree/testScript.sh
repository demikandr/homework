for i in `seq 10`
do
	./testGenerator $1 $i > test
	time ./Dec_tree < test > dTreeResults
	time ./Vlob < test > VlobResults
	diff dTreeResults VlobResults
done
