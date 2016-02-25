#include "KHeap.h"
#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>

int main() {
    std::priority_queue <double> heap;
    double newEl;
    int c;
    while (1) {
		scanf("%d",&c);
		switch(c) {
			case 1: {
				scanf("%lf",&newEl);
				heap.push(-newEl);
				break;
			}
			case 2: {
				printf("%lf\n",-heap.top());
				break;
			}
			case 3: {
				heap.pop();
				break;
			}
			case 4: {
				return 0;
			}
		}

    }
}
