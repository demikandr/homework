#include <iostream>
#include <vector>
#include <algorithm>

#include <my-includes/myLib.h>

int main() {
    int sizeOfVector, countOfTests;
    std::cin >> countOfTests;
    std::cin >> sizeOfVector;
    std::vector <int> vect;
    std::cout << countOfTests << ' ' << sizeOfVector << std::endl;
    for (int i=0;i<countOfTests;++i) {
		scanVector(vect,sizeOfVector);
		std::sort(vect.begin(),vect.end());
		printVector(vect);
		std::cout << std::endl;
	}



    return 0;
}
