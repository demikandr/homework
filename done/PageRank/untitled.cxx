#include <random>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

std::uniform_int_distribution<uint32_t> ubool_dist(0, 1);

const int REALYIMPORTANTCONST=10;//правда очень важная константа

std::map< std::string, std::set < std::string> > dictionary;
std::vector < std::string> words;


class Graph {
	private:
		std::vector <double> pageRank;
		typedef std::mt19937 RNG;
		const double EPS=0.0000000000001;
		const double d=0.85;
		RNG rng;
		double size;
		std::vector < std::vector < int > > graph;
		bool pageRankReady;		
	public:
		Graph() {}
		Graph(std::map <std::string, std::set <std::string> > dictionary);
		void initByRandom(const int& size);
		void initByRandom(const int& size, const int& seed);
		std::vector<double> getPageRank();
		void printGraph();
	
};

Graph::Graph(std::map < std::string, std::set < std::string> > dictionary) {
	pageRankReady=false;
	int i=0;
	std::map < std::string, int> tWords;
	for (auto it=dictionary.begin();it!=dictionary.end();++it) {
		words.push_back(it->first);
		tWords[it->first]=i;
		i++;
	}
	graph.resize(i);
	pageRank.resize(i);
	for (auto it=dictionary.begin();it!=dictionary.end();++it) {
		for (auto subIt=it->second.begin();subIt!=it->second.end();++subIt) {
			graph[tWords[*subIt]].push_back(tWords[it->first]);
			graph[tWords[it->first]].push_back(tWords[*subIt]);
		}
	}
	size=i;
}

void Graph::printGraph() {
	for (size_t i=0;i<graph.size();++i) {
		std::cout << i << ": ";
		for (size_t j=0;j<graph[i].size();++j) {
			std::cout << graph[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Graph::initByRandom(const int& size, const int& seed) {
	rng.seed(seed);
	graph.resize(size);
	pageRank.resize(size);
	Graph::size=size;
	for (size_t i=0;i<graph.size();++i) {
		for (size_t j=0;j<graph.size();++j) {
			if (ubool_dist(rng)&&(i!=j)) {
				graph[i].push_back(j);
			}
		}
	}
}

void Graph::initByRandom(const int& size) {
	initByRandom(size, 0);
}

std::vector <double>  Graph::getPageRank() {
	if (pageRankReady) {
		return pageRank;
	}
	double error=1;
	for (size_t i=0;i<graph.size();++i) {
		pageRank[i]=1/(size);
	}
	std::vector<double> tempPageRank(graph.size());
	int count=0;
	while(error>EPS) {
		count++;
		error=0;
		for (size_t i=0;i<graph.size();++i) {
			tempPageRank[i]=(1-d)/size;
		}
		for (size_t i=0;i<graph.size();++i) {
			for (size_t j=0;j<graph[i].size();++j) {
				if (i!=j) {
					tempPageRank[graph[i][j]]+=d*pageRank[i]/((double)graph[i].size());
				}
			}
		}
		for (size_t i=0;i<graph.size();++i) {
			error=std::max(error, 2*std::abs(tempPageRank[i]-pageRank[i])/(pageRank[i]+tempPageRank[i]));
			pageRank[i]=tempPageRank[i];
			tempPageRank[i]=0;
		}
	}
	std::cout << count << std::endl;
	pageRankReady=true;
	return pageRank;
}

bool isLetter(char a) {
	return (('a'<=a)&&(a<='z'));
}

void readFile() {
	std::vector < std::string> tWords;
	std::string newWord;
	while(!std::cin.eof()) {
		std::cin >> newWord;
		//std::transform(newWord.begin(), newWord.end(), newWord.begin(), ::tolower);
		tWords.push_back(newWord);
		for (size_t i=std::max(0, ((int) tWords.size()-REALYIMPORTANTCONST));i<tWords.size()-1;++i) {
			dictionary[newWord].insert(tWords[i]);
			dictionary[tWords[i]].insert(newWord);
		}
		
	}
}



int main(int argc, char **argv)
{
	//~ int n, seed;
	//~ std::cin >> n >> seed;
	//~ std::vector < double > result;
	//~ Graph graph;
	//~ graph.initByRandom(n, seed);
	//~ result=graph.getPageRank();
	//graph.printGraph();
	//~ for (int i=0;i<n; ++i ) {
		//~ std::cout << result[i] << ' ';
	//~ }
	//~ std::cout << std::endl;
	//~ //////////////////////////////////////
	//~ for (int i=1;i<argc;++i) {
		//~ readFile(argv[i]);
	//~ }
	//~ 
	readFile();
	Graph graph(dictionary);
	std::vector <std::pair < double, std::string > > result; 
	for (size_t i=0;i<words.size();++i) {
		result.push_back(make_pair(graph.getPageRank()[i], words[i]));
	}
	sort(result.rbegin(), result.rend());
	for (size_t i=0;i<result.size();++i) {
		std::cout << result[i].second << ' ';
	}
	return 0;
}

