#include <set>
#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	std::ifstream commonWordsFile;
	commonWordsFile.open(argv[1]);
	std::set < std::string> commonWords;
	while (!commonWordsFile.eof()) {
		std::string word;
		commonWordsFile >> word;
		commonWords.insert(word);
	}
	while(!std::cin.eof()) {
		std::string word;//, tWord, ttWord;
		std::cin >> word;
		//~ tWord=word;
		//~ ttWord=word;
		//~ if (tWord.size()>5) {
			//~ tWord.pop_back();
		//~ }
		//~ if (ttWord.size()>6) {
			//~ ttWord.pop_back();
			//~ ttWord.pop_back();
		//~ }
		if ((commonWords.find(word)==commonWords.end())) {//&&(commonWords.find(tWord)==commonWords.end())&&(commonWords.find(ttWord)==commonWords.end())){
			std::cout << word << std::endl;
		}
	}
	return 0;
}

