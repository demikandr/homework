
for i in `seq 10`
do
        echo "new iteration"
	./generateRandomGraph $1 $2 $((3+i)) > test # вершин ребер зерно
	./boostGraph/untitled < test > boostResult
	./myGraph/getMinPaths 1-kBFS < test > 1-kBFSResult
	./myGraph/getMinPaths dijkstra < test > dijkstraResult
	echo "first diff"
	diff 1-kBFSResult boostResult
	echo "second diff"
	diff 1-kBFSResult dijkstraResult
done 
