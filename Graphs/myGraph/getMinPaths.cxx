#include <vector>
#include <iostream>
#include "graph.h"
#include <stdlib.h>
#include <cstring>

	


void printVector(std::vector <int> vector) {
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
  //  std::cerr <<  time_span.count()<<  std::endl;
	for (size_t i=0;i<vector.size();++i) {
		std::cout << ((vector[i]==-1 )?2147483647:vector[i]) << ", ";
		
		
	}
	std::cout << std::endl;
}
int main(int argc, char **argv)
{
	//~ if (argc!=2) {
		//~ std::cerr << "Arguments: type of algorithm (1-kBFS or dijkstra)" << std::endl;
		//~ return 1;
	//~ }
	int countOfVerticles;
	std::cin >> countOfVerticles;
	std::vector < Edge > edges;
	Edge newEdge;
	
	for (int i=0, auto it=edges.begin();!std::cin.eof();++i) {
		
		std::cin >> newEdge.from >> newEdge.to >> newEdge.weight;
		edges.push_back(newEdge);
	}
	
	Graph graph(edges, countOfVerticles);
	//std::cout << graph;
	
	if (strcmp(argv[1],"1-kBFS")==0) {
		printVector(graph.getDistancesFrom(1, KBFS));
	}
	else {
		printVector(graph.getDistancesFrom(1, DIJKSTRA));
	}
	return 0;
}

