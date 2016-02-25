for i in `seq 10`	
do
	./testGenerator $1 $2 $i > test
	time  ./segmentTree < test > segmentTreeOutput
	time ./simplePalindromes < test > simplePalindromesOutput
	diff segmentTreeOutput simplePalindromesOutput
done
