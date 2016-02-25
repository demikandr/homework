
echo '' > result
for i in `seq 20`
do
 ./untitled $i >> result
 echo "hey "
 echo $i
 echo " "
done
