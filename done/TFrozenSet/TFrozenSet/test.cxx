#include "TFrozenSet.h"
#include <iostream>

int test(int n) {
	std::vector<int> v;
	v.resize(n);
	for (int i=0;i<n;++i) {
		std::cin >> v[i];
	}
	
	TFrozenSet<std::vector<int>::iterator, int> hashTable(v.begin(),v.end());
	//std::cout << "built";
	//std::cin >> temp;
	for (int i=0;i<n;++i) {
		int temp;
		std::cin >>  temp;
		std::cout << (hashTable.Contains(temp) ? "contains" : "not contains") << std::endl;
	}
	
	return 0;
}
int main() {
	int n,countOfTests;
	std::cin >> countOfTests >> n;
	for (int i=0; i<countOfTests;++i) {
		test(n);
	}
	return 0;
}
