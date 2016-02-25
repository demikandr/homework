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
	std::cout << countOfVerticles << std::endl;
	for (int i = 0; i < countOfEdges; ++i) { //  оценочно мамтожидание коллизии при попытке полного заполнения одна коллиция
		std::uniform_int_distribution<int> uint_dist_255(0, 255);
		std::uniform_int_distribution<int> uint_dist(0, countOfVerticles-1);
		std::cout << uint_dist(rng) << ' ' << uint_dist(rng) << ' ' << uint_dist_255(rng) << std::endl;
	}
	
	return 0;
}

