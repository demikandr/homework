#include <cctype>
#include <iostream>
#include <ctype.h>

int main(int argc, char **argv)
{
	char ch;
	while(!std::cin.eof()) {
		std::cin >> std::noskipws >> ch;
		if ((('a'<=ch)&&(ch<='z'))||isspace(ch)  ) {
			std::cout <<  ch;
		}
		if (('A'<=ch)&&(ch<='Z')) {
			ch+='a'-'A';
			std::cout << ch;
		}
	}
	return 0;
}

