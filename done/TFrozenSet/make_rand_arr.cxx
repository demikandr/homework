#include <iostream>
#include "my-includes/myLib.h"


int main() {
	int vectorSize, seed, countOfVectors;
	std::cin >> countOfVectors >> vectorSize >> seed;
	std::cout << countOfVectors << ' ' << vectorSize<< std::endl;
	std::vector <int> v;
	for (int i=0;i<2*countOfVectors;++i) {
		generateRandomVector(v, vectorSize, seed);
		printVector(v);
		seed++;
	}
    return 0;
}
