//~ Входные данные - диапазон чисел, количество команд, [зерно].

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

std::uniform_int_distribution<uint32_t> uint_dist(0, 100000);
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


void printRandomCommand(int &treeSize, Random& rand) {
	int begin, end;
	begin=rand.getRandomInt()%treeSize;
	end=rand.getRandomInt()%(treeSize-begin) + 1+begin;
	std::cout << begin << ' ' << end << ' ' <<rand.getRandomInt()%(end-begin);
}

int main(int argc, char **argv)
{
	Random rand(std::stoi(argv[3]));
	int treeSize=std::stoi(argv[1]);
	std::cout << treeSize << std::endl;
	for (int i=0;i<treeSize;++i) {
		std::cout << rand.getRandomInt() << ' ';
	}
	std::cout << std::endl;
	for (int i=0;i<std::stoi(argv[2]);++i) {
		printRandomCommand(treeSize, rand);
		std::cout << std::endl;
	}
	return 0;
}
