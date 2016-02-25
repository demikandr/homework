#!/bin/bash
#set -x
CC=g++
CFLAGS=-O
input_file=$1
filename=${input_file%%.cxx}
#/usr/bin/time 
$CC  -std=c++11 -o $filename.out $CFLAGS $input_file
rc=$? #return code last process

if [[ $rc -eq 0 ]]; then
   time  ./$filename.out
   exit $?
fi

exit $rc
