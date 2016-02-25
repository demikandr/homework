#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	int sizeOfArray, begin, end, n;
	std::cin >> sizeOfArray;
	std::vector<int> arr(sizeOfArray);
	for (int i=0;i<sizeOfArray;++i) {
		std::cin >>arr[i];
	}
	std::vector<int> tArr;
	while(!std::cin.eof()) {
		std::cin >> begin >> end >> n;
		tArr.insert(tArr.begin(),arr.begin(), arr.end());
		std::nth_element(tArr.begin()+begin, tArr.begin()+begin+n, tArr.begin()+end);
		std::cout << tArr[begin+n] << std::endl;
		tArr.clear();
	}
	return 0;
}

