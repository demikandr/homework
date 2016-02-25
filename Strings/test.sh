
t=$3
for i in `seq 10`
do
        echo "new iteration"
	./generateRandomString $1 $2 $((t+i)) > test # вершин ребер зерно
	./main < test > ahoCorasickResult
	./dumbFindTemplate < test > dumbAlgorithmResult
	echo "diff"
	diff ahoCorasickResult dumbAlgorithmResult
done 
