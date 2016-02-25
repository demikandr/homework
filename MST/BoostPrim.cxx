#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace boost;

int num_nodes;


main(int, char *[])
{
  typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property < edge_weight_t, long int > > graph_t;
    //~ typedef compressed_sparse_row_graph<  undirectedS,
		//~ no_property, property < edge_weight_t, long int_t >  > graph_t;
    

  typedef graph_traits < graph_t >::edge_descriptor edge_descriptor;
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef std::pair<int, int> Edge;


	std::vector <Edge> graphSource;
	std::vector < long int > weights;
  std::cin>>  num_nodes;
  while (!std::cin.eof()) {
	int from, to;
	double  weight;
	std::cin >> from >> to >> weight;
	
	graphSource.push_back(std::make_pair(from, to));
	weights.push_back((int)weight);
  }
  
  
  int num_arcs = graphSource.size();
  graph_t g(graphSource.begin(), graphSource.end(), weights.begin(), num_nodes);
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> pp(num_vertices(g));
//~ property_map < graph_t, edge_weight_t >::type weight = get(edge_weight, g);
	  
	  
	  
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  prim_minimum_spanning_tree(g, &pp[0]);

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;
  //~ std::cerr << "fuck\n";
  //~ std::cout << "distances and parens:" << std::endl;
  for (std::size_t i = 0; i != pp.size(); ++i) {
    if (pp[i] != i) {
      std::cout << "parent[" << i << "] = " << pp[i] << std::endl;
  }
    else {
      std::cout << "parent[" << i << "] = no parent" << std::endl;
  }
  }
    //~ std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    //~ std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
