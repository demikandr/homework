
echo $1' '$2 | ./generateRandomGraph $3  > test
./Boruvka < test > BR 
./Prima < test > PR 
./Kruskal  < test > KR 
echo "first diff"	
diff BR PR
echo "second diff"
diff BR KR
 
