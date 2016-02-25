#include <iostream>
#include <vector>

#include <my-includes/myLib.h>
#include "TTopElements(line).cxx"

int main() {
    int countOfMax, sizeOfVector, countOfTests;
    std::cin >> countOfTests;
    std::cin >> countOfMax;
    TTopElements<int> yatte(countOfMax);
    std::vector <int> vect;
    std::cout << countOfTests << ' ' << countOfMax << std::endl;
    for (int i=0;i<countOfTests;++i) {
		std::cin >> sizeOfVector;
		scanVector(vect,sizeOfVector);
		for (int i=0;i<sizeOfVector;++i) {
			yatte.Add(vect[i]);
		}
		std::vector<int> result;
		yatte.GetCurrentTop(result);
		printVector(result);
		std::cout << std::endl;
	}



    return 0;
}
