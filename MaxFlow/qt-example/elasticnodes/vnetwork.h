#ifndef VNETWORK_H
#define VNETWORK_H

#include "../../network.h"

class Node;
class Edge;
class MaxFlow;
class GraphWidget;
class QGraphicsScene;

const int SCENE_WIDTH=1600, SCENE_HEIGHT=800;

class VNetwork:public Network
{
private:
    std::vector<std::vector<Edge*> >VEdges;
    std::vector<Node*> VNodes;
    MaxFlow* algo;
public:
    void initSideData(GraphWidget* widget);
    VNetwork(Network& network):Network(network), algo(NULL) {

    }


public:
    int doNextStep(QGraphicsScene* scene);
    int doPreviousStep(QGraphicsScene *scene);
    void drawVNetwork(QGraphicsScene *scene);
    void bindAlgo(MaxFlow* maxFlow);
};

#endif // VNETWORK_H
