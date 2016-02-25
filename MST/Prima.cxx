#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <chrono>

const long double INF=20.0;

struct Edge {
	int from;
	int to;
	long double weight;
	Edge(int from, int to, long double weight): from(from), to(to), weight(weight) {}
	Edge() {}
	bool operator<(Edge other) const
    {
        return (( weight > other.weight) || ((weight == other.weight)&&(std::make_pair(from, to) > std::make_pair(other.from, other.to))));
    }

};

class Graph {
	private:
		std::vector < std::vector < std::pair < int, long double > > > 	graph;//verticleTo, weight
		std::vector < Edge > 									_prima(int verticle);
	public:
																Graph(std::vector < Edge > edges, int countOVerticles );
		std::vector < Edge > 									getMST();
		void													printGraph();
		friend std::ostream& 									operator<<(std::ostream& os, const Graph& graph) ;
			
};



Graph::Graph(std::vector <  Edge > edges, int countOfVerticles) {
	graph.resize(countOfVerticles);
	for (size_t i=0;i<edges.size();++i) {
		graph[edges[i].from].push_back(std::make_pair(edges[i].to, edges[i].weight));
	}
}

std::vector < Edge > Graph::getMST() {
		return _prima(0);
}

struct greater1{
  bool operator()(const Edge& a,const Edge& b) const{
    return a.weight>b.weight;
  }
};

std::vector < Edge > Graph::_prima(int verticle) {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::priority_queue < Edge, std::vector < Edge > ,greater1 > heap;
	Edge edge(-1, -1, INF);
	std::vector < Edge > result;
	std::vector <int> hasResult(graph.size(), -1);
	edge.from=verticle;
	edge.to=verticle;
	edge.weight=0;
	heap.push(edge);//вершина и расстояние
	unsigned int counter=0;
	while (!heap.empty()&&(counter < graph.size())) {
		Edge tVerticle=heap.top();
		heap.pop();
		if (hasResult[tVerticle.to]==-1) {
			hasResult[tVerticle.to]=1;
			result.push_back(tVerticle);
			counter++;
			for (size_t i=0; i < graph[tVerticle.to].size(); ++i) {
				if (hasResult[graph[tVerticle.to][i].first]==-1) {
					std::pair < int, long double > ttVerticle=graph[tVerticle.to][i];
					edge.from=tVerticle.to;
					edge.to=ttVerticle.first;
					edge.weight=ttVerticle.second;
					heap.push(edge);
				}
			}
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long double> time_span = std::chrono::duration_cast<std::chrono::duration<long double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;
	return result;	
}


std::ostream& operator<< (std::ostream& os, const Graph& graph) {
	os << "Graph:" << std::endl;
	for (size_t i=0; i < graph.graph.size(); ++i) {
		os << i << ":\t";
		for (size_t j=0; j < graph.graph[i].size(); ++j) {
			os << graph.graph[i][j].first << ", ";
		}
		os << std::endl;
	}
}

void printVector(std::vector <int> vector) {
	for (size_t i=0;i<vector.size();++i) {
		std::cout << vector[i] << ", ";
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	size_t countOfVerticles;
	std::cin >> countOfVerticles;
	std::vector < Edge > edges, result;
	Edge newEdge;
	
	for (int i=0;(std::cin >> newEdge.from >> newEdge.to >> newEdge.weight);++i) {
		edges.push_back(newEdge);
		std::swap(newEdge.from, newEdge.to);
		edges.push_back(newEdge);
	}
	Graph graph(edges, countOfVerticles);
	//std::cout << graph;
	
	result=graph.getMST();

    
    for (size_t i = 0; i < countOfVerticles-1; ++i) {
		if (result[i].from<result[i].to) {
			std::swap(result[i].from, result[i].to);
		}
	}
	std::sort(result.begin(), result.end());
	std::cout << countOfVerticles << std::endl;
	for (size_t i = 0; i < countOfVerticles-1; ++i) {
		if (result[i].from<result[i].to) {
			std::swap(result[i].from, result[i].to);
		}
		std::cout << result[i].from << ' '<< result[i].to  << ' ' << result[i].weight << std::endl;
	}
	return 0;
}

//~ std::vector < Edge > Graph::_prima(int verticle) {
	//~ auto comp=[](const std::pair<int, long double>& lhs, const std::pair<int, long double>& rhs) -> bool {
             //~ if (lhs.second == 0)
                 //~ return true;
             //~ return lhs.second > rhs.second; } ;
	//~ std::priority_queue < std::pair < int, long double >, std::vector < std::pair < int, long double > >,decltype(comp) > heap(comp);
	//~ std::vector < int > result(graph.size(), -1);
	//~ heap.push(std::make_pair(verticle, 0));//вершина и расстояние
	//~ while (!heap.empty()) {
		//~ std::pair < int, long double > tVerticle=heap.top();
		//~ heap.pop();
		//~ if (result[tVerticle.first]==-1) {
			//~ result[tVerticle.first]=tVerticle.second;
			//~ Edge edge(tVerticle.
			//~ edgeResult.push_back(
			//~ for (size_t i=0; i < graph[tVerticle.first].size(); ++i) {
				//~ std::pair < int, int > ttVerticle=graph[tVerticle.first][i];
				//~ heap.push(std::make_pair(ttVerticle.first, ttVerticle.second));
			//~ }
		//~ }
	//~ }
	//~ return result;	
//~ }
