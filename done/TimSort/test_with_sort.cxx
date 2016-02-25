#include <iostream>
#include <vector>
#include <my-includes/myLib.h>
#include <algorithm>

#include "TimSort/TimSort.h"	

bool comp(const int a, const int b) {
	return a < b;
}

int main(int argc, char **argv)
{
	int sizeOfVector;
	std::vector < int > vect;
	std::cin >> sizeOfVector;
	scanVector(vect,sizeOfVector);
	std::sort(vect.begin(),vect.end(),comp);
	assert(std::is_sorted(vect.begin(),vect.end()));
	printVector(vect);
	return 0;
}

