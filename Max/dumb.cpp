#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>


void findMax(const std::vector<int>& vector, int beginInd, int endInd, int& maximum){
	maximum = vector[beginInd];
	for (int i = beginInd + 1; i < endInd; ++i) {
		maximum = std::max(maximum, vector[i]);
	}
}



int main ()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	int countOfThreads = std::thread::hardware_concurrency();
	std::cout << "CountOfThreads could be " << countOfThreads << std::endl;
	if (countOfThreads == 0) {
		countOfThreads = 4;
	}
	std::vector <std::thread> threads;
	int n;
	std::cin >> n;
	std::vector<int> vector(n);
	vector[0] = 0;
	for (int i = 1; i < n; ++i) {
		vector[i] = vector[i-1]*1664525 + 1013004223;
	}
	int segmentSize = (n)/countOfThreads;
	start = std::chrono::system_clock::now();
	int maxEl = *std::max_element(vector.begin(), vector.end());
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << elapsed_seconds.count() << std::endl;
	std::cout << maxEl << std::endl;
	return 0;
}
