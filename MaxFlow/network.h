//
// Created by demikandr on 9/25/15.
//

#pragma once
#ifndef NETWORK_H
#define NETWORK_H


#include <iostream>
#include <vector>
#include <assert.h>

class Network {//addCapacit, getCapacity, getEdgesFrom
    protected:
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
        Network(int countOfNodes, const std::vector <int>& from, const std::vector <int> &to, const std::vector<long long int> &capacities):
            countOfNodes(countOfNodes),
            countOfEdges(from.size()),
            adjacencyMatrix(countOfNodes, std::vector<long long int> (countOfNodes)),
            adjacencyList(countOfNodes),
            current(countOfNodes)
        {
            assert(((int)to.size() == countOfEdges) && ((int)capacities.size() == countOfEdges));
            for (int i = 0; i < countOfEdges; ++i) {
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

        void printGraph() const {
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
        int getCountOfNodes() const {
            return countOfNodes;
        }
        int getCountOfEdges() const {
            return countOfEdges;
        }
        int getNextEdgeDestFrom(int node) {
            if (current[node] == (int) adjacencyList[node].size()) {
                current[node]=0;
                return -1;
            }
            return adjacencyList[node][current[node]++];
        }

        int getCapacity(int from, int to) const {
            return adjacencyMatrix[from][to];
        }

};

#endif