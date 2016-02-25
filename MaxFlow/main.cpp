#include <iostream>
#include "flow.h"
#include "network.h"

#include <vector>
#include <limits>

const long long INF=std::numeric_limits<long long>::max();








int main() {
    std::ios_base::sync_with_stdio(false);
    int countOfNodes, countOfEdges;
    std::cin >> countOfNodes >> countOfEdges;
    std::vector <int> from(countOfEdges), to(countOfEdges);
    std::vector <long long int> capacity(countOfEdges);
    for (int i = 0; i < countOfEdges; ++i) {
        std::cin >> from[i] >> to[i] >> capacity[i];
        --from[i], --to[i];
    }
    Network network(countOfNodes, from, to, capacity);
    //network.printGraph();
    //std::cerr << "printed graph\n";
    MaxFlow maxFlow(network);
    //maxFlow.getResidualNetwork().printGraph();

    return 0;
}