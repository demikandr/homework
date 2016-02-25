#include <vector>
#include <iostream>
#include <random>
#include <set>

typedef std::mt19937 RNG;
RNG rng;
std::uniform_int_distribution<int> uint_dist;
std::uniform_real_distribution<long double> ureal_dist(0.0, 1.0);
int countOfVerticles, counter=0;

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
				return element = getRoot(parent[element]);
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
				counter++;
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
	bool operator<(Edge other) const
    {
        return (std::make_pair(from, to) < std::make_pair(other.from, other.to)) ;
    }

};

std::set < Edge> edges;

Edge getRandomEdge(int countOfVerticles) {
	Edge edge;
	edge.from=uint_dist(rng)%countOfVerticles;
	edge.to=uint_dist(rng)%countOfVerticles;
	edge.weight=ureal_dist(rng);
	return edge;
}

bool notExists(Edge edge) {
	return (edges.find(edge)==edges.end());
}

void add(Edge edge) {
	edges.insert(edge);
	std::cout << edge.from << ' ' << edge.to << ' ' << edge.weight << std::endl;

}

int main(int argc, char **argv)
{
	int percentOfEdges, countOfEdges;
	rng.seed(((argc==2)?std::atoi(argv[1]):0));
	std::cin >> countOfVerticles >> percentOfEdges;
	countOfEdges=countOfVerticles*(countOfVerticles-1)*percentOfEdges/200;
	std::cout << countOfVerticles << std::endl;
	DisjointSet verticles(countOfVerticles);
	Edge newEdge;
	for (int i = 0; i < countOfEdges || counter< countOfVerticles-1; ++i) {
		while(1) {
			newEdge=getRandomEdge(countOfVerticles);
			if (notExists(newEdge)) {
				add(newEdge);
				verticles.unionSets(newEdge.from, newEdge.to);
				break;
			}
		}
	}
	
	return 0;
}

