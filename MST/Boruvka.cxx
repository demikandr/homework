#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

const double INF=200.0;

class DisjointSet {
	public: 
			std::vector<int> parent, rank;
			DisjointSet(size_t sizeOfSource): parent(sizeOfSource), rank(sizeOfSource) {
				for ( size_t i = 0; i < sizeOfSource; ++i) {
					parent[i] = i;
				}
			}
			
			
			int getRoot(int element) { 
				if (parent[element] == element) {
					return element;
				}
				return parent[element] = getRoot(parent[element]);
			}
			
			
			bool isEqual(int first, int second) {
				return (getRoot(first) == getRoot(second));
			}
			
			void unionSets(int first, int second) {
				first = getRoot(first);
				second = getRoot(second);
				
				if (first == second) {
					return;
				}
				if (rank[first] == rank[second]) {
					++rank[second];
				}
				if (rank[first] > rank[second]) {
					parent[second] = first;
				}
				else {
					parent[first] = second;					
				}
			}
};

struct Edge {
	int from;
	int to;
	long double weight;
	Edge(int from, int to, double weight): from(from), to(to), weight(weight) {}
	Edge() {}
	bool operator<(Edge other) const
    {
        return (( weight < other.weight) || ((weight == other.weight)&&(std::make_pair(from, to) < std::make_pair(other.from, other.to))));
    }

};

void read (size_t& countOfVerticles, std::vector < Edge > & edges) {
	std::cin >> countOfVerticles;
	Edge tEdge;
	while(std::cin >> tEdge.from >> tEdge.to >> tEdge.weight) {
		edges.push_back(tEdge);
	}
}

int main(int argc, char **argv)
{
	size_t countOfVerticles;
	std::vector <Edge> edges, result;
	read(countOfVerticles, edges);
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	DisjointSet verticles(countOfVerticles);
	
	while (result.size() < countOfVerticles-1) {
		
		Edge edge(-1, -1, INF);
		std::vector<Edge> minEdges(countOfVerticles, edge);
		for (size_t i=0;i<edges.size(); ++i) {
			if (!verticles.isEqual(edges[i].from, edges[i].to)) {
				if (minEdges[verticles.getRoot(edges[i].from)].weight > edges[i].weight) {
					minEdges[verticles.getRoot(edges[i].from)] = edges[i];
				}
				if (minEdges[verticles.getRoot(edges[i].to)].weight > edges[i].weight) {
					minEdges[verticles.getRoot(edges[i].to)] = edges[i];
				}
			}
		}
		for (size_t i=0; i < countOfVerticles; ++i) {
			
			if ((minEdges[i].from != -1)&&(!verticles.isEqual(minEdges[i].from,minEdges[i].to))) {
				result.push_back(minEdges[i]);
				verticles.unionSets(minEdges[i].from, minEdges[i].to);
			}
		}
	}
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;
    for (size_t i = 0; i < countOfVerticles-1; ++i) {
		if (result[i].from<result[i].to) {
			std::swap(result[i].from, result[i].to);
		}
	}
	std::sort(result.rbegin(), result.rend());
	std::cout << countOfVerticles << std::endl;
	for (size_t i = 0; i < countOfVerticles-1; ++i) {
		
		if (result[i].from<result[i].to) {
			std::swap(result[i].from, result[i].to);
		}
		std::cout << result[i].from << ' '<< result[i].to << ' ' << result[i].weight << std::endl;
	}
	return 0;
}
