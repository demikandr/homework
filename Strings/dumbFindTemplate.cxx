#include <string>
#include <iostream>
#include <assert.h>

int main(int argc, char **argv)
{
	std::string word, text;
	std::cin >> word >> text;
	assert(word.length() > 0);
	for (int i = 0; i < (int)  text.size() - (int) word.size() + 1; ++i) {
		bool equal = true;
		for (int j = 0; j < (int)word.size(); ++j) {
			if ((word[j] != text[i + j]) && (word[j]!='?')) {
				equal = false;
				break;
			}
		}
		if (equal) {
			std::cout << i << std::endl;
		}
	}
	return 0;
}

