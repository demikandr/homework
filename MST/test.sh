#set -x
rm BoruvkaTime
rm PrimaTime
rm KraskalaTime
rm BoostPrimTime
rm BoostKruskalTime
for i in `seq 10`
do
	for j in `seq 10`
	do
		echo $i'0 percentage '$j' round'
		echo $1' '$((i*10)) | ./generateRandomGraph $((2+j))  > test
		./Boruvka < test > BR 2>> BoruvkaTime
		./Prima < test > PR 2>> PrimaTime
		./Kruskal  < test > KR 2>> KraskalaTime
		./BoostPrim < test > BPR 2>> BoostPrimTime
		./BoostKruskal < test > BKR 2>> BoostKruskalTime
		echo "first diff"	
		diff BR PR
		echo "second diff"
		diff BR KR
	done
done 