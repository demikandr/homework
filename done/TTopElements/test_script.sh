#!/bin/bash

g++ -std=c++0x -o make_rand_arr -O2 make_rand_arr.cxx
g++ -std=c++0x -o line/line -O2 line/test.cxx
g++ -std=c++0x -o stable/stable -O2 stable/test.cxx
g++ -std=c++0x -o sortt -O2 sort.cxx

./make_rand_arr <seed_1000000 > input
time ./line/line <input >outputs/output_line
time ./stable/stable <input > outputs/output_stable
./sortt < outputs/output_line > outputs/output_line_sorted
./sortt < outputs/output_stable > outputs/output_stable_sorted
if cmp outputs/output_line_sorted outputs/output_stable_sorted; then
	echo "correct"
else
	echo "wtf"
fi
