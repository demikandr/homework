#include <vector>
#include <iostream>
#include "graph.h"


void printVector(std::vector <int> vector) {
	for (size_t i=0;i<vector.size();++i) {
		std::cout << vector[i] << ", ";
	}
	std::cout << std::endl;
}
int main(int argc, char **argv)
{
	int countOfVerticles;
	std::cin >> countOfVerticles;

	//~ std::vector < Edge > edges(n);
	
	//~ for (int i=0;i<n;++i) {
		//~ std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
	//~ }
	
	//~ Graph graph(edges, countOfVerticles);
	Graph graph(countOfVerticles, 0, 0.5);
	std::cout << graph;
	std::cout << "with kbfs\n";
	printVector(graph.getDistancesFrom(1, KBFS));
	std::cout << "with dijkstra\n";
	printVector(graph.getDistancesFrom(1, DIJKSTRA));
	return 0;
}

