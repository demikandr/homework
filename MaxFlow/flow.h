/*
 * Flow.h
 * 
 * Copyright 2015 Unknown <demikandr@demikandr-laptop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#pragma once
#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "network.h"

//Убрать длинные строки, деструктор для history/ умными указателями
const int UP_ACTION = 0;
const int PUSH_ACTION = 1;
const int OUT_OF_HISTORY_ACTION = 2;

struct Action {
    int  type;
    int from;
    int to;
    int node;
    int changeInCapacity;
    int changeInHeight;
    Action(int actionType, int from, int to, int changeInCapacity):
            type(actionType),
            from(from),
            to(to),
            changeInCapacity(changeInCapacity)
    {assert(actionType==PUSH_ACTION);}
    Action(int actionType, int node, int changeInHeight):
            type(actionType),
            node(node),
            changeInHeight(changeInHeight)
    {assert(actionType==UP_ACTION);}
    Action(int actionType): type(actionType){};
};

const Action OUT_OF_HISTORY(OUT_OF_HISTORY_ACTION);

class MaxFlow {
    private:
        Network residualNetwork;
        int SOURCE, SINK;
        std::vector < long long int > overflow;
        std::vector < int> height;
        std::vector <int>  current;
        std::vector<Action*> history;
        int step;
        long long int maxFlowValue;

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
            history.push_back(new Action(PUSH_ACTION, from, to, diff));
            residualNetwork.addCapacity(from, to, -diff);
            residualNetwork.addCapacity(to, from, diff);
            //std::cerr << "push" << '\t' << from << '\t' << to << '\t' << diff << std::endl;
        }

        void up(int node) {
            history.push_back(new Action(UP_ACTION, node, 1));
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
        MaxFlow( const Network& baseNetwork):
                residualNetwork(baseNetwork),
                SOURCE(0),
                SINK(baseNetwork.getCountOfNodes()-1),
                overflow(baseNetwork.getCountOfNodes()),
                height(baseNetwork.getCountOfNodes()),
                current(baseNetwork.getCountOfNodes())

        {

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
            for (int  i = 0; i < baseNetwork.getCountOfNodes(); ++i) {
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
        Action stepForward() {
            if (step == (int) history.size()) {
                return OUT_OF_HISTORY;
            }
            return *history[step++];
        }
        Action stepBack() {
            if (step == 0) {
                return OUT_OF_HISTORY;
            }

            return *history[--step];
        }
};

#endif
		

	

