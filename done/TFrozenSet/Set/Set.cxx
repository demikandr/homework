#include <set>
#include <stdio.h>
#include <iostream>
#include <vector>

int test(int n) {
	std::vector<int> v;
	v.resize(n);
	for (int i=0;i<n;++i) {
		std::cin >> v[i];
	}
	std::set<int> hashTable(v.begin(),v.end());
	for (int i=0;i<n;++i) {
		int temp;
		std::cin >>  temp;
		std::cout << ((hashTable.find(temp)!=hashTable.end()) ? "contains" : "not contains") << std::endl;
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
