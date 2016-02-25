#include <iostream>
#include "TAutoGradient.h"
#include <math.h>


template<typename T>
T f(const T &t) {
	return sin(t)*sin(t)+cos(t)*cos(t);
}
int main() {
	double n;
	std::cin >> n;
	TAutoGradient<double> t(n,1);
	std::cout << f< double >(n) << std::endl << f<TAutoGradient<double> >(t);
	
	return 0;
}
