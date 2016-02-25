#include <iostream>
#include <set>
#include <random>
#include <string>
#include <assert.h>


typedef std::mt19937 RNG;
		
class Random{
	private:
		RNG rng;
		std::uniform_int_distribution<uint32_t> uint_dist;
	public:
		Random(int seed);
		Random();
		int getRandomInt();		
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

int main() {
	Random random;
	for (int i=0;i<10;++i) {
		std::cout << random.getRandomInt() << std::endl;
	}
	return 0;
}
