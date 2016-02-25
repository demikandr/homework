
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	std::vector<int> vector;
	int begin, end, val, pos;
	std::string command;
	while (!std::cin.eof()) {
		std::cin >> command;
		switch(command[0]) {
			case 'u':
				std::cin >> val >> pos;
				vector[pos]=val;
				break;
			case 's':
				std::cin >> begin >> end;
				
				std::cout << std::accumulate(vector.begin()+begin, vector.begin()+end, 0);
				break;
			case 'g':
				std::cin >> pos;
				std::cout << vector[pos];
				break;
			case 'p':
				if (command[1]=='u') {
					std::cin >> val >> pos;
					vector.insert(vector.begin()+pos, val);
				}
				else {
				}
				break;
			case 'n':
				std::cin >> begin >> end;
				std::next_permutation(vector.begin()+begin, vector.begin()+end);
				break;
		}
		//~ std::cout << std::endl;
		//~ for (int i=0;i<vector.size();++i) {
			//~ std::cout << vector[i] << ' ';
		//~ }
		std::cout << std::endl;
	}
	return 0;
}

