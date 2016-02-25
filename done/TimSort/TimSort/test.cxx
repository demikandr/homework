#include <iostream>
#include <vector>
#include <my-includes/myLib.h>
#include <algorithm>
#include <assert.h>

#include "TimSort.h"	

bool comp(const int a, const int b) {
	return a < b;
}

int main(int argc, char **argv)
{
	int sizeOfVector,countOfVectors;
	std::vector < int > vect;
	std::cin >> countOfVectors >> sizeOfVector;
	for (int i=0;i<countOfVectors;++i){
		scanVector(vect,sizeOfVector);
		TimSort<int, std::vector <int>::iterator, bool(const int, const int)> TimSort(vect.begin(),vect.end(),comp);
		assert(std::is_sorted(vect.begin(),vect.end()));
		printVector(vect);
	}
	return 0;
}

