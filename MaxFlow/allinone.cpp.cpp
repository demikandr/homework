#include <iostream>

#include <vector>
#include <limits>

#include <iostream>
#include <vector>
#include <assert.h>

class Network {//addCapacit, getCapacity, getEdgesFrom
private:
    int countOfNodes;
    int countOfEdges;
    /*struct Edge {
        int to;
        int capacity;
        Edge(int to, int capacity):to(to), capacity(capacity){}
    };*/
    std::vector< std::vector<long long int> > adjacencyMatrix;
    std::vector< std::vector<int> > adjacencyList;
    std::vector <int> current;

public:
    Network(int countOfNodes, std::vector <int> from, std::vector <int> to, std::vector<long long int> capacities):countOfNodes(countOfNodes), countOfEdges(from.size()), adjacencyMatrix(countOfNodes, std::vector<long long int> (countOfNodes)), adjacencyList(countOfNodes), current(countOfNodes) {
        countOfEdges=from.size();
        Network::countOfNodes=countOfNodes;
        //assert((to.size() == countOfEdges) && (capacities.size() == countOfEdges);
        for (int i=0; i < countOfEdges; ++i) {
            adjacencyMatrix[from[i]][to[i]]=capacities[i];
            adjacencyList[from[i]].push_back(to[i]);
            adjacencyList[to[i]].push_back(from[i]);
        }
    }
    void addCapacity(int from, int to, long long int changeInCapacity) {
        adjacencyMatrix[from][to] += changeInCapacity;
        //adjacencyMatrix[to][from] -= changeInCapacity;
        assert(adjacencyMatrix[from][to] >= 0);
        //assert(adjacencyMatrix[to][from] >= 0);
    }
    std::vector < int> getEdgesFrom(int node) {
        return adjacencyList[node];
    }
    void printGraph() {
        for (int i = 0; i < countOfNodes; ++i) {
            std::cout << '\t' << i;
        }
        std::cout << std::endl;
        for (int i = 0; i < countOfNodes; ++i) {
            std::cout << i;
            for (int j = 0; j < countOfNodes; ++j) {
                std::cout << '\t' << adjacencyMatrix[i][j];
            }
            std::cout << std::endl;
        }
    }
    int getCountOfNodes() {
        return countOfNodes;
    }
    int getCountOfEdges() {
        return countOfEdges;
    }
    int getNextEdgeDestFrom(int node) {
        if (current[node] == (int) adjacencyList[node].size()) {
            current[node]=0;
            return -1;
        }
        return adjacencyList[node][current[node]++];
    }

    int getCapacity(int from, int to) {
        return adjacencyMatrix[from][to];
    }

};
class MaxFlow {//исправить, что наговнил
private:
    int SOURCE, SINK;
    std::vector < long long int > overflow;
    std::vector < int> height;
    std::vector <int>  current;
    long long int maxFlowValue;
    Network residualNetwork;
    void push(int from, int to) {
        long long diff = residualNetwork.getCapacity(from, to);
        if (from != SOURCE) {
            diff=std::min(diff, overflow[from]);
        }
        if ((from != SOURCE) && (from != SINK)) {
            overflow[from] -= diff;
        }
        if ((to != SOURCE) && (to != SINK)) {
            overflow[to] += diff;
        }
        residualNetwork.addCapacity(from, to, -diff);
        residualNetwork.addCapacity(to, from, diff);
        //std::cerr << "push" << '\t' << from << '\t' << to << '\t' << diff << std::endl;
    }

    void up(int node) {
        ++height[node];
    }

    bool discharge (int node) {
        //std::cerr << "has begun discharge\n";
        bool somethingHappened = false;
        do {
            for (; (current[node] != -1) && ((overflow[node] > 0) or (node == SOURCE)); ) {
                int dest = current[node];
                if ((height[dest] < height[node]) && (residualNetwork.getCapacity(node, dest)>0)) {
                    //std::cerr << "push\n";
                    push(node, dest);
                    somethingHappened = true;
                }
                else {
                    //std::cerr << "nextCur\n";
                    current[node]=residualNetwork.getNextEdgeDestFrom(node);
                }
                //std::cerr << "current[node] " << current[node] << "[" << node << "]" << std::endl;
            }
            if (overflow[node] > 0) {

                //std::cerr << "try up current[node] " << current[node] << "[" << node << "]" << std::endl;
                current[node]=residualNetwork.getNextEdgeDestFrom(node);
                up(node);
                somethingHappened = true;
            }
        } while (overflow[node] > 0);
        return somethingHappened;

    }
public:
    //MaxFlow(Network& baseNetwork, std::vector<int> from = *(new std::vector<int>), std::vector<int> to = *(new std::vector<int>)): SOURCE(0), SINK(residualNetwork.getCountOfNodes()-1),overflow(residualNetwork.getCountOfNodes()), height(residualNetwork.getCountOfNodes()),current(residualNetwork.getCountOfNodes()) {
    MaxFlow(Network& baseNetwork): SOURCE(0), SINK(baseNetwork.getCountOfNodes()-1),overflow(baseNetwork.getCountOfNodes()), height(baseNetwork.getCountOfNodes()),current(baseNetwork.getCountOfNodes()), residualNetwork(baseNetwork) {
        height[0]=baseNetwork.getCountOfNodes();
        for (int i = 0; i < residualNetwork.getCountOfNodes(); ++i ) {
            current[i]=residualNetwork.getNextEdgeDestFrom(i);
        }
        bool somethingHappened;
        do {
            somethingHappened = false;
            for (int i = 0; i < residualNetwork.getCountOfNodes(); ++i) {
                if (discharge(i)) {
                    somethingHappened=true;
                }
            }
        } while (somethingHappened);
        maxFlowValue = 0;
        for (int i = 0; i < baseNetwork.getCountOfNodes(); ++i) {
            maxFlowValue+=baseNetwork.getCapacity(0, i) - residualNetwork.getCapacity(0, i);
        }
        std::cout << maxFlowValue << std::endl;
        /*for (int i = 0; i < edges.size ; ++i) {
            capacity[i]=std::min(capacity[i], -residualNetwork[from[i]][to[i]]);
            std::cout << std::endl << std::max(capacity[i],(long long int) 0);
            residualNetwork[from[i]][to[i]]+=capacity[i];
        }*/
    }
    Network getResidualNetwork() {
        return residualNetwork;
    }
    long long int getMaxFlowValue() {
        return maxFlowValue;
    }

};
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
}//
// Created by demikandr on 10/15/15.
//

