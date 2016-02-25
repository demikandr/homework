#include <random>
#include <iostream>

int main(int argc, char **argv)
{
	int countOfVerticles, countOfEdges;
	typedef std::mt19937 RNG;
		RNG rng;
		rng.seed(std::atoi(argv[3]));
	countOfVerticles=atoi(argv[1]);
	countOfEdges=atoi(argv[2]);
	std::cout << countOfVerticles << ' ' << countOfEdges << std::endl;
	for (int i = 0; i < countOfEdges; ++i) { //  оценочно мамтожидание коллизии при попытке полного заполнения одна коллиция
		std::uniform_int_distribution<int> uint_dist_capacity(0, 1000000);
		std::uniform_int_distribution<int> uint_dist(1, countOfVerticles);
		std::cout << uint_dist(rng) << ' ' << uint_dist(rng) << ' ' << uint_dist_capacity(rng) << std::endl;
	}
	
	return 0;
}

