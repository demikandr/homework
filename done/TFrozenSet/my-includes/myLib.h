#include <iostream>
#include <random>
#include <vector>
#include <stdio.h>

typedef std::mt19937 MyRandNumGen;
MyRandNumGen randNumGen;
std::uniform_int_distribution<uint32_t> randNum(0,1000000008);
std::uniform_int_distribution<uint32_t> randPr(0,100);

void generateRandomVector(std::vector <int> &vector, const int sizeOfVector, const int seed) {
	vector.resize(sizeOfVector);
	randNumGen.seed(seed);
	vector.resize(sizeOfVector);
	randNumGen.seed(seed);
	for (int i = 0; i < sizeOfVector; ++i) {
		vector[i]=randNum(randNumGen);
	}
}
void generateRandomRangeVector(std::vector <int> &vector, const int sizeOfVector, const int seed) {
	vector.resize(sizeOfVector);
	randNumGen.seed(seed);
	std::uniform_int_distribution<uint32_t> randEl(0,sizeOfVector-1);
	for (int i = 0; i < sizeOfVector; ++i) {
		vector[i]=i;
	}
	for (int i = 0; i < sizeOfVector; ++i) {
			std::swap(vector[i],vector[randEl(randNumGen)]);
	}
}
void generateRandomVector(std::vector <int> &vector, const int sizeOfVector) {
	vector.resize(sizeOfVector);
	randNumGen.seed(0);
	for (int i = 0; i < sizeOfVector; ++i) {
		vector[i]=randNum(randNumGen);
	}
}
void generateRandomUpVector(std::vector <int> &vector, const int sizeOfVector, const int seed) {
	vector.resize(sizeOfVector);
	randNumGen.seed(seed);
	std::uniform_int_distribution<uint32_t> randEl(0,sizeOfVector-1);
	for (int i = 0; i < sizeOfVector; ++i) {
		vector[i]=i;
	}
	for (int i = 0; i < sizeOfVector; ++i) {
		//if (randPr(randNumGen)<10)
			vector[i]=randEl(randNumGen);
	}
}
void printVector(const std::vector <int> &vect) {
    for (int i = 0; i < vect.size(); ++i) {
        printf("%d ",vect[i]);
	}
	printf("\n");
}
void scanVector(std::vector <int> &vect, const int sizeOfVector) {
	vect.resize(sizeOfVector);
	for (int i = 0; i < sizeOfVector; ++i) {
        scanf("%d ",&vect[i]);
    }
}
