#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
//~ #include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace boost;

int num_nodes;


main(int, char *[])
{
  typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property < edge_weight_t, long double > > graph_t;
    //~ typedef compressed_sparse_row_graph<  directedS,
		//~ no_property, property < edge_weight_t, double_t >  > graph_t;
    
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef graph_traits < graph_t >::edge_descriptor edge_descriptor;
  typedef std::pair<int, int> Edge;


	std::vector <Edge> graphSource;
	std::vector < long double > weights;
  std::cin>>  num_nodes;
  while (!std::cin.eof()) {
	int from, to;
	long double  weight;
	std::cin >> from >> to >> weight;
	graphSource.push_back(std::make_pair(from, to));
	weights.push_back(weight);
  }
  
  int num_arcs = graphSource.size();
  //~ graph_t g(boost::edges_are_unsorted,graphSource.begin(), graphSource.end(), weights.begin(), num_nodes);
  graph_t g(graphSource.begin(), graphSource.end(), weights.begin(), num_nodes);
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(1, g);
	std::vector <unsigned int> pp(num_nodes);
property_map < graph_t, edge_weight_t >::type weight = get(edge_weight, g);
  std::vector < edge_descriptor > spanning_tree;
  
  
  
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
  	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr <<  time_span.count()<<  std::endl;

  std::cout << "Print the edges in the MST:" << std::endl;
  for (std::vector < edge_descriptor >::iterator ei = spanning_tree.begin();
       ei != spanning_tree.end(); ++ei) {
    std::cout << source(*ei, g) << " <--> " << target(*ei, g)
      << " with weight of " << weight[*ei]
      << std::endl;
  }

  std::ofstream fout("figs/kruskal-eg.dot");
  fout << "graph A {\n"
    << " rankdir=LR\n"
    << " size=\"3,3\"\n"
    << " ratio=\"filled\"\n"
    << " edge[style=\"bold\"]\n" << " node[shape=\"circle\"]\n";
  graph_traits<graph_t>::edge_iterator eiter, eiter_end;
  for (boost::tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
    fout << source(*eiter, g) << " -- " << target(*eiter, g);
    if (std::find(spanning_tree.begin(), spanning_tree.end(), *eiter)
        != spanning_tree.end())
      fout << "[color=\"black\", label=\"" << get(edge_weight, g, *eiter)
           << "\"];\n";
    else
      fout << "[color=\"gray\", label=\"" << get(edge_weight, g, *eiter)
           << "\"];\n";
  }
  fout << "}\n";
  
  return EXIT_SUCCESS;
}
