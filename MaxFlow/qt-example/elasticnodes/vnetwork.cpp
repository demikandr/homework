#include "vnetwork.h"
#include "graphwidget.h"
#include "node.h"
#include "edge.h"
#include "../../flow.h"

void VNetwork::initSideData(GraphWidget* widget) {
    VNodes.resize(countOfNodes);
    VEdges.resize(countOfNodes);
    for (int i = 0; i < countOfNodes; ++i) {
        VEdges[i].resize(countOfNodes);
    }
    for (int i = 0; i < countOfNodes; ++i ) {
        VNodes[i] = new Node(widget, ((i == 0)? countOfNodes : 0) );
        VNodes[i]->setPos(i,i*i);
    }
    VNodes.front()->setPos(-SCENE_WIDTH/2+30, 0);
    VNodes.back()->setPos(SCENE_WIDTH/2-30, 0);
    VNodes.front()->fix();
    VNodes.back()->fix();
    for (int i = 0; i < countOfNodes; ++i ) {
        for (int j = 0; j < countOfNodes; ++j) {
            VEdges[i][j] = new Edge(VNodes[i], VNodes[j], getCapacity(i, j));
        }
    }
}

void VNetwork::drawVNetwork(QGraphicsScene *scene) {
    for (int i = 0; i < countOfNodes; ++i ) {
        std::cout << "add node to the scene\n";
        scene->addItem(VNodes[i]);
    }
    for (int i = 0; i < (int) VEdges.size(); ++i ) {
        for (int j = 0; j < countOfNodes; ++j) {
            if (adjacencyMatrix[i][j]>0) {
                scene->addItem(VEdges[i][j]);
            }
        }
    }
}
void VNetwork::bindAlgo(MaxFlow* maxFlow) {
    algo = maxFlow;
}

int VNetwork::doNextStep(QGraphicsScene *scene) {
    Action action=algo->stepForward();
    if (action.type == OUT_OF_HISTORY_ACTION) {
        return 1;
    }
    if (action.type == PUSH_ACTION) {
        addCapacity(action.from, action.to, -action.changeInCapacity);
        addCapacity(action.to, action.from, action.changeInCapacity);
        if (getCapacity(action.from, action.to) == 0) {
            scene->removeItem(VEdges[action.from][action.to]);
        }
        if (getCapacity(action.to, action.from)==action.changeInCapacity) {
            scene->addItem(VEdges[action.to][action.from]);
        }

    }
    if (action.type == UP_ACTION) {
        VNodes[action.node]-> up(action.changeInHeight);
    }
    return 0;
}
int VNetwork::doPreviousStep(QGraphicsScene *scene) {
    Action action=algo->stepBack();
    if (action.type == OUT_OF_HISTORY_ACTION) {
        return 1;
    }
    if (action.type == PUSH_ACTION) {
        std::cout << "It realy backward push\n";
        if (getCapacity(action.from, action.to) == 0) {

            scene->addItem(VEdges[action.from][action.to]);
        }
        if (getCapacity(action.to, action.from)==action.changeInCapacity) {
            scene->removeItem(VEdges[action.to][action.from]);
        }
        addCapacity(action.from, action.to, action.changeInCapacity);
        addCapacity(action.to, action.from, -action.changeInCapacity);
    }
    if (action.type == UP_ACTION) {
        VNodes[action.node]-> up(-action.changeInHeight);
    }
    return 0;
}
