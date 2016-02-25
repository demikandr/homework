#include <string>
#include <iostream>
#include <assert.h>

int main(int argc, char **argv)
{
	std::string  string, command;
	int pos, begin, end;
	char val;
	std::cin >> string;
	int t=0;
	while(!std::cin.eof()) {
		std::cin >> command;
		switch (command[0]) {
			case 'u':
				std::cin >> val >> pos;
				string[pos]=val;
				break;
			case 'i':
				std::cin >> begin >> end;
				t=1;
				for (int i=begin; i<end;++i) {
					if (string[i]!=string[end-i-1+begin]) {
						t=0;
					}
				}
				std::cout << t << std::endl;
				break;
		}
	}
	return 0;
}

