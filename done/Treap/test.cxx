#include <vector> 
#include <iostream>

#include "Treap.h"

int main() {
	node t=NULL;
	int m;
	long long int p1=115249, p2=127,n;
	std::cin >> n >> m;
	for (long long int i=1; i<=n;i++) {//printTree(t);
		insert(t,(int) (p1*i+p2)%n,i,i);
		//std::cout << "fuck" << i << std::endl;
	}
	int last=0;
	//printTree(t);
	//std::cout << std::endl;
	for (int i=0;i<n;i++) {
		last=del(t,(last+m+n-i-1)%(n-i)+1);
		//~ printTree(t);
		//~ std::cout << std::endl;
		//~ std::cout << last << std::endl;
	}
	return 0;
}
