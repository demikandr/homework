for i in `seq 10`
do	
	result=0.0 
	read x
	result+=x
	echo "$result / 10" | bc -l	
done
echo "$result / 10"

