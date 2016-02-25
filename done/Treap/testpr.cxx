#include <vector> 
#include <iostream>
#include <stdio.h>

#include "Treap.h"

int main() {
	int m,n;
	std::vector<int> v;
	std::cin >> n >> m;
	for (long long int i=1; i<=n;i++) {//printTree(t);
		v.push_back(i);
		//std::cout << "fuck" << i << std::endl;
	}
	int last=-1;
	//printTree(t);
	//std::cout << std::endl;
	for (int i=0;i<n;i++) {
		
		printf("another bitches son is %d\n",v[(last+m)%(n-i)]);
		
		v[(last+m)%(n-i)]=0;
		last=(last+m)%(n-i)-1;
		for (int j=0;j<(n-i)-1;++j) {
			if (v[j]==0) {
				std::swap(v[j],v[j+1]);
			}
		}
		//~ printTree(t);
		//~ std::cout << std::endl;
		//~ std::cout << last << std::endl;
	}
	return 0;
}
