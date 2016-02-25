
#include <iostream>

int main(int argc, char **argv)
{
	char ch;
	while(!std::cin.eof()) {
		scanf("%c",&ch);
		if (((('a'<=ch)&&(ch<='z'))||(('A'<ch)&&(ch<='Z')))||isspace(ch) ) {
			printf("%c", ch);
		}
	}
	return 0;
}

