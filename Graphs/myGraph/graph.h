#include <vector>
#include <deque>
#include <iostream>
#include <queue>
#include <random>
#include <chrono>

#include <limits>

#define KBFS 1
#define DIJKSTRA 2
std::chrono::high_resolution_clock::time_point t1;

struct Edge {
	int from;
	int to;
	int weight;
};

class Graph {
	private:
		std::vector < std::vector < std::pair < int, int > > > 	graph;//verticleTo, weight
		std::vector < int > 									_kbfs();
		std::vector < int >  									_kBFS(int verticle);
		std::vector < int > 									_dijkstra(int verticle);
		//~ void 													_initByRandom(int countOfVerticles, int seed, double probability);
	public:
																//~ Graph(int countOfVerticles, int seed = 0, double probability = 0.5);
																Graph(std::vector < Edge > edges, int countOVerticles );
		std::vector <int> 										getDistancesFrom(int verticle, int type=KBFS);
		void													printGraph();
		friend std::ostream& 									operator<<(std::ostream& os, const Graph& graph) ;
			
};

//~ void Graph::_initByRandom(int countOfVerticles, int seed, double probabilityOfEdge) {
	//~ rng.seed(seed);
	//~ std::uniform_int_distribution<int> unit_dist_255(0, 255);
	//~ graph.resize(countOfVerticles);
	//~ for (int i = 0;i < countOfVerticles; ++i) {
		//~ for (int j = 0; j<countOfVerticles; ++j) {
			//~ if ( (std::generate_canonical<double,std::numeric_limits<double>::digits>(rng)  < probabilityOfEdge)&&(j != i ) ) {
				//~ graph[i].push_back(std::make_pair(j, unit_dist_255(rng)));
			//~ }
		//~ }
	//~ }
//~ }
//~ 
//~ Graph::Graph(int countOfVerticles,  int seed, double probability) {
	//~ _initByRandom(countOfVerticles, seed, probability);
//~ }

Graph::Graph(std::vector <  Edge > edges, int countOfVerticles) {
	graph.resize(countOfVerticles);
	for (size_t i=0;i<edges.size();++i) {
		graph[edges[i].from].push_back(std::make_pair(edges[i].to, edges[i].weight));
	}
}

std::vector < int > Graph::getDistancesFrom(int verticle, int type) {
	
	if (type==KBFS) {
		return _kBFS(verticle);
	}
	if (type==DIJKSTRA) {
		return _dijkstra(verticle);
	}
}
std::vector < int > Graph::_dijkstra(int verticle) {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	auto comp=[](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) -> bool {
             //~ if (lhs.second == 0)
                 //~ return true;
             return lhs.second > rhs.second; } ;
	std::priority_queue < std::pair < int, int >, std::vector < std::pair < int, int > >,decltype(comp) > heap(comp);
	std::vector < int > result(graph.size(), -1);
	heap.push(std::make_pair(verticle, 0));//вершина и расстояние
	size_t fuck=0;
	
	while (!heap.empty() && (fuck<graph.size())) {
		std::pair < int, int > tVerticle=heap.top();
		heap.pop();
		if (result[tVerticle.first]==-1) {
			++fuck;
			result[tVerticle.first]=tVerticle.second;
			for (size_t i=0; i < graph[tVerticle.first].size(); ++i) {
				std::pair < int, int > ttVerticle=graph[tVerticle.first][i];
				heap.push(std::make_pair( ttVerticle.first, ttVerticle.second+tVerticle.second));
			}
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;
	return result;	
}
std::vector < int > Graph::_kBFS(int verticle) {
	t1 = std::chrono::high_resolution_clock::now();
	std::deque < std::pair < int, int> > deque;//verticle, delay
	std::vector < int > result(graph.size(), -1);
	deque.push_back(std::make_pair(verticle, 0));
	deque.push_back(std::make_pair(-1,0));
	int length=0;
	while ( !deque.empty()) {
		std::pair < int, int > tVerticle=deque.front();
		if (tVerticle.first==-1) {
			++length;
			deque.pop_front();
			if (deque.empty()) {
				break;
			}
			deque.push_back(std::make_pair(-1, -1));
			continue;
		}
		if (result[tVerticle.first]!=-1) {
			deque.pop_front();
			continue;
		}
		if (tVerticle.second>0) {
			deque.push_back( std::make_pair( tVerticle.first, tVerticle.second - 1 ) );
			deque.pop_front();
			continue;
		}
		result[tVerticle.first]=length;
		deque.pop_front();
		for (size_t i=0;i<graph[tVerticle.first].size();++i) {
			std::pair <int, int> ttVerticle=graph[tVerticle.first][i];
			if (result[ttVerticle.first]==-1) {
				if (ttVerticle.second==0) {
					deque.push_front(std::make_pair(ttVerticle.first, ttVerticle.second));
				}
				else {
					deque.push_back(std::make_pair(ttVerticle.first, ttVerticle.second-1));
				}
			}
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
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
