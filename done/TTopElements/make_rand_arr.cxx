#include <iostream>
#include <my-includes/myLib.h>


int main() {
	int vectorSize, parameter, seed, countOfTests;
	std::cin >> countOfTests >> vectorSize >> seed >> parameter;
	std::vector <int> v;
	std::cout << countOfTests << ' ' << parameter << std::endl;
	for (int i=0; i<countOfTests;++i) {
		std::cout << vectorSize<< std::endl;
		generateRandomVector(v, vectorSize, seed+i);
		printVector(v);
		std::cout << std::endl;
	}
		
		
    return 0;
}
