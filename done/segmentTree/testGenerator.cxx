//~ Входные данные -     , количество команд, [зерно].

#include <iostream>
#include <random>
#include <string>

const int COUNT_OF_COMMANDS=1;

#define UPDATE 0
#define IS_PALINDROME 1

typedef std::mt19937 RNG;

std::uniform_int_distribution<uint32_t> uint_dist(0,1000000000);
std::uniform_int_distribution<uint32_t> uint_command_dist(0, COUNT_OF_COMMANDS);

class Random{
	private:
		RNG rng;
	public:
		Random(int seed);
		Random();
		int getRandomInt();
		int getRandomCommand();		
		std::string getRandomString(int sizeOfString);
};

Random::Random(int seed) {
	rng.seed(seed);
}

Random::Random() {
	rng.seed(0);
}
int Random::getRandomInt() {
	return uint_dist(rng);
}

int Random::getRandomCommand() {
	return uint_command_dist(rng);
}

std::string Random::getRandomString(int sizeOfString) {
	std::string string;
	int lOfPal=1;
	for (int i=0;i<sizeOfString;++i) {
		string.push_back('A'+getRandomInt()%56);
		if (getRandomInt()%10==0) {
			lOfPal=getRandomInt()%i;
			for (int j=i-lOfPal;j<i;++j) {
				string[j]=string[i-j];
			}
		}
	}
	return string;
}


void printRandomCommand(int treeSize, Random& rand) {
	int begin;
	begin=rand.getRandomInt()%treeSize;
	switch (rand.getRandomCommand()) {
		case UPDATE:
			std::cout << "updateChar " <<(char) ('A'+rand.getRandomInt()%56) << ' ' << rand.getRandomInt()%treeSize;
			break;
		case IS_PALINDROME:
			std::cout << "isPalindrome " << begin << ' ' << rand.getRandomInt()%(treeSize-begin) + 1+begin;
			break;
	}
}

int main(int argc, char **argv)
{
	
	Random rand(std::stoi(argv[3]));
	std::cout << rand.getRandomString(std::stoi(argv[1])) << std::endl;
	for (int i=0;i<std::stoi(argv[2]);++i) {
		printRandomCommand((std::stoi(argv[1])), rand);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

