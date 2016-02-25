#include "KHeap.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>



int main(int argc, char ** argv) {
	KHeap<double> kHeap(std::atoi(argv[1]));
	//std::cout << atoi(argv[1]) << std::endl;
	
    int c;
    double newEl;
    //std::cout << "fuck" << k;
    //clock_t start = clock();

    while (1) {
		scanf("%d",&c);
		switch(c) {
			case 1: {
				scanf("%lf",&newEl);
				kHeap.push(newEl);
				break;
			}
			case 2: {
				printf("%lf\n",kHeap.getMin());
				break;
			}
			case 3: {
				kHeap.pop();
				break;
			}
			case 4: {
				return 0;
			}
		}

    }
    //clock_t end = clock();
   //std::cout << (end-start)/CLOCKS_PER_SEC << ' ' << k << std::endl;
	
	return 0;
}
