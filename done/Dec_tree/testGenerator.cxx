//~ Входные данные - количество команд, [зерно].

#include <iostream>
#include <set>
#include <random>
#include <string>
#include <assert.h>
#include <set>

const int COUNT_OF_COMMANDS=3;

#define PUSH 0
#define UPDATE 1
#define SUM 2
#define NEXT_PERM 3

typedef std::mt19937 RNG;

std::uniform_int_distribution<uint32_t> uint_dist(0, 10000000);
std::uniform_int_distribution<uint32_t> uint_command_dist(0, COUNT_OF_COMMANDS);

class Random{
	private:
		RNG rng;
	public:
		Random(int seed);
		Random();
		int getRandomInt();
		int getRandomCommand();		
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


void printRandomCommand(int &treeSize, Random& rand, int countOfCommands) {
	int begin;
	if (treeSize==0) {
		std::cout << "push " << rand.getRandomInt() << " " << 0;
		++treeSize;
		return;
	}
	begin=rand.getRandomInt()%treeSize/2;
	switch ((treeSize<countOfCommands/2) ? PUSH:rand.getRandomCommand()) {
			case PUSH:
				std::cout << "push " << rand.getRandomInt() << " " << rand.getRandomInt()%(treeSize+1);
				++treeSize;
				break;
			case UPDATE:
				std::cout << "update " <<rand.getRandomInt() << ' ' << rand.getRandomInt()%treeSize;
				break;
			case SUM:
				std::cout << "sum " << begin << ' ' << rand.getRandomInt()%(treeSize-begin) + 1+begin;
				break;
			case NEXT_PERM:
				std::cout << "next_permutation " << begin << ' ' << rand.getRandomInt()%(treeSize-begin) + 1+begin;
				break;
			case 4:
				break;
		}
}

int main(int argc, char **argv)
{
	
	Random rand(std::stoi(argv[2]));
	int treeSize=0;
	for (int i=0;i<std::stoi(argv[1]);++i) {
		printRandomCommand(treeSize, rand, std::stoi(argv[1]));
		std::cout << std::endl;
	}
	return 0;
}

