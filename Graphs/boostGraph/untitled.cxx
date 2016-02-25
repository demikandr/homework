#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>

using namespace boost;

int num_nodes;


main(int, char *[])
{
  //~ typedef adjacency_list < listS, vecS, directedS,
    //~ no_property, property < edge_weight_t, int > > graph_t;
    typedef compressed_sparse_row_graph<  directedS,
		no_property, property < edge_weight_t, int >  > graph_t;
    
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef std::pair<int, int> Edge;


	std::vector <Edge> graphSource;
	std::vector < int > weights;
  std::cin>>  num_nodes;
  while (!std::cin.eof()) {
	int from, to, weight;
	std::cin >> from >> to >> weight;
	graphSource.push_back(std::make_pair(from, to));
	weights.push_back(weight);
  }
  
  int num_arcs = graphSource.size();
  graph_t g(boost::edges_are_unsorted,graphSource.begin(), graphSource.end(), weights.begin(), num_nodes);
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(1, g);
	
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  dijkstra_shortest_paths(g, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;
  
  //~ std::cout << "distances and parens:" << std::endl;
  graph_traits < graph_t >::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
	  std::cout << d[*vi] <<  ", ";
    //~ std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    //~ std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;

  //~ std::ofstream dot_file("figs/dijkstra-eg.dot");
//~ 
  //~ dot_file << "digraph D {\n"
    //~ << "  rankdir=LR\n"
    //~ << "  size=\"4,3\"\n"
    //~ << "  ratio=\"fill\"\n"
    //~ << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

  //~ graph_traits < graph_t >::edge_iterator ei, ei_end;
  //~ for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    //~ graph_traits < graph_t >::edge_descriptor e = *ei;
    //~ graph_traits < graph_t >::vertex_descriptor
      //~ u = source(e, g), v = target(e, g);
    //~ dot_file << u << " -> " << v
      //~ << "[label=\"" << get(weightmap, e) << "\"";
    //~ if (p[v] == u)
      //~ dot_file << ", color=\"black\"";
    //~ else
      //~ dot_file << ", color=\"grey\"";
    //~ dot_file << "]";
  //~ }
  //~ dot_file << "}";
  return EXIT_SUCCESS;
}
