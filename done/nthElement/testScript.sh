for i in `seq 10`
do
	./testGenerator $1 $2 $i > test #длина массива, количество запросов, зерно
	time ./nthElement < test > nthElementOut
	time ./simpleNthElement < test > simpleNthElementOut
	diff nthElementOut simpleNthElementOut
done
