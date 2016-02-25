#include <random>
#include <iostream>

int main(int argc, char **argv)
{
	int sizeOfWord, sizeOfText;
	typedef std::mt19937 RNG;
		RNG rng;
		rng.seed(std::atoi(argv[3]));
	sizeOfWord = atoi(argv[1]);
	sizeOfText = atoi(argv[2]);
	for (int i = 0; i < sizeOfWord; ++i) { //  оценочно мамтожидание коллизии при попытке полного заполнения одна коллиция
		std::uniform_int_distribution<int> uint_dist_char('a', 'a'+25);
		std::uniform_int_distribution<int> uint_dist_isQ(1, 5);
		if (uint_dist_isQ(rng) == 1) {
			std::cout << '?';
		}
		else {
			std::cout << (char) uint_dist_char(rng);
		}
		
	}
	std::cout << std::endl;
	for (int i = 0; i < sizeOfText; ++i) { //  оценочно мамтожидание коллизии при попытке полного заполнения одна коллиция
		std::uniform_int_distribution<int> uint_dist_char('a', 'a'+25);
		std::cout << (char) uint_dist_char(rng);
	}
	std::cout << std::endl;
	return 0;
}

