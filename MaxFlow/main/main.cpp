#include <iostream>
//#include "graph.h"
//#include "flow.h"
#include <vector>
#include <limits>

const long long INF=std::numeric_limits<long long>::max();



class MaxFlow{

};
const int MAX_NODE=1000, MAX_EDGE=20000;
int SOURCE=0, SINK;
int countOfNodes, countOfEdges;
long long residualNetwork[MAX_NODE][MAX_NODE];
long long height[MAX_NODE], overflow[MAX_NODE], capacity[MAX_EDGE], from[MAX_EDGE], to[MAX_EDGE];
int current[MAX_NODE], countOfEdgesFrom[MAX_NODE], edges[MAX_NODE][MAX_NODE*2];

long long baseNetwork[MAX_NODE][MAX_NODE];
bool nothingHappened;


void push(int from, int to) {
    long long diff = residualNetwork[from][to];
    if (from != SOURCE) {
        diff=std::min(diff, overflow[from]);
    }
    if ((from != SOURCE) && (from != SINK)) {
        overflow[from] -= diff;
    }
    if ((to != SOURCE) && (to != SINK)) {
        overflow[to] += diff;
    }
    residualNetwork[from][to]-=diff;
    residualNetwork[to][from]+=diff;
    // std::cerr << "push" << '\t' << from << '\t' << to << '\t' << diff << std::endl;
}

void up(int node) {
    ++height[node];
}

void discharge (int node) {
    do {
        for (; (current[node] < countOfEdgesFrom[node]) && ((overflow[node] > 0) or (node == SOURCE)); ) {
            if ((height[edges[node][current[node]]] < height[node]) && (residualNetwork[node][edges[node][current[node]]] > 0)) {
                push(node, edges[node][current[node]]);
                nothingHappened = false;
            }
            else {
                ++current[node];
            }
            //std::cerr << "current[node] " << current[node] << "[" << node << "]" << std::endl;
        }
        if (overflow[node] > 0) {
            //std::cerr << "try up current[node] " << current[node] << "[" << node << "]" << std::endl;
            current[node]=0;
            up(node);
            nothingHappened = false;
        }
    }while (overflow[node] > 0);

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin >> countOfNodes >> countOfEdges;

    SINK = countOfNodes-1;
    height[0]=countOfNodes;
    for (int i = 0; i < countOfEdges; ++i) {
        std::cin >> from[i] >> to[i] >> capacity[i];
        --from[i], --to[i];
        residualNetwork[from[i]][to[i]]+=capacity[i];
        edges[from[i]][countOfEdgesFrom[from[i]]]=to[i];
        edges[to[i]][countOfEdgesFrom[to[i]]]=from[i];
        ++countOfEdgesFrom[from[i]];
        ++countOfEdgesFrom[to[i]];
    }


    do {
        nothingHappened = true;
        for (int i = 0; i < countOfNodes; ++i) {
            discharge(i);
        }
    } while (!nothingHappened);

    long long result = 0;
    for (int i = 0; i < countOfEdges; ++i) {
        residualNetwork[from[i]][to[i]]-=capacity[i];
    }
    for (int i = 0; i < countOfNodes; ++i) {
        result-=residualNetwork[0][i];
    }
    std::cout << result;
    /*for (int i = 0; i < countOfEdges ; ++i) {
        capacity[i]=std::min(capacity[i], -residualNetwork[from[i]][to[i]]);
        std::cout << std::endl << std::max(capacity[i],(long long int) 0);
        residualNetwork[from[i]][to[i]]+=capacity[i];
    }*/
    return 0;
}