#include <iostream>

class DisjointSet {
	public: 
			std::vector<int> parent, size;
			DisjointSet(size_t sizeOfSource): parent(sizeOfSource), size(sizeOfSource, 1) {
				for ( size_t i = 0; i < sizeOfSource; ++i) {
					parent[i] = i;
				}
			}
			bool isEqual(int first, int second) {
				return (getRoot(first) == getRoot(second));
			}
			int getRoot(int element) {
				if (parent[element] == element) {
					return element;
				}
				return (element = getRoot(element));
			}
			void unionSets(int first, int second) {
				first = getRoot(first);
				second = getRoot(second);
				if (size[first] > size[second) {
					parent[second] = first;
					size[first] += size[second];
				}
				else {
					parent[first] = second;
					size[second] += size[first];
				}
			}
}

struct Edge {
	int from;
	int to;
	int weight;
	bool operator<(Edge other) const
    {
        return weight < other.weight;
    }

};

void read (int& countOfVerticles, DisjointSet& verticles, std::vector < Edge > & edges) {
	std::cin >> countOfVerticles;
	DisjointSet verticles(countOfVerticles);
	while(!std::cin.eof()) {
		Edge tEdge;
		std::cin >> tEdge.from >> tEdge.to >> tEdge.weight;
		edges.push_back(tEdge);
	}
}

int main(int argc, char **argv)
{
	int countOgVerticles;
	DisjointSet verticles;
	std::vector <Edge> edges;
	read(countOfVerticles, verticles, edges);
	std::sort(edges.begin(), edges.end());
	for (size_t i = 0; ( (i < edges.size() ) && ( result.size <= countOfVerticles ) ); ++i) {
		if (!verticles.isEqual(edges[i].from, edges[i].to)) {
			result.push_back(edges[i]);
			verticles.unionSets(edges[i].from, edges[i].to);
		}
	}
	
	std::cout << countOfVerticles;
	for (int i = 0; i < countOfVerticles; ++i) {
		
	return 0;
}

