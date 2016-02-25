#include <iostream>
//
// Created by demikandr on 10/28/15.
//

//
// Created by demikandr on 10/28/15.
//


#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
//
// Created by demikandr on 11/6/15.
//


const int COUNTOFLETTERS = 28;
struct Node {
    int len, link;
    std::vector<int> go;
    Node(int len): len(len), link(-1), go(COUNTOFLETTERS, -1) {assert(len >= 0);}
};

std::vector<Node> nodes;
const int rootId = 0, blankId = 1;
int lastId = rootId;
Node node(0);
std::vector<long long int>  d;

 long long int dFunction(int nodeId) {
    assert(d[nodeId] != -1);
    assert(nodeId < nodes.size());
    assert(nodeId != blankId);
    if (d[nodeId] > 0) {
        return d[nodeId];
    }
    d[nodeId] = 1;
    for (int i = 0; i < COUNTOFLETTERS; ++i) {
        if (nodes[nodeId].go[i] != -1) {
            //std::cout << nodeId << " " << (char) (i+ 'a') << " " << nodes[nodeId].go[i] << std::endl;
            d[nodeId] += dFunction(nodes[nodeId].go[i]);
        }
    }
    return d[nodeId];
}

void addLetter(char letter) {
    //std::cout << "add char " << letter << ", lastId is " << lastId << std::endl;
    nodes.push_back(node);
    int curId = nodes.size() - 1;
    nodes[curId].len = nodes[lastId].len + 1;
    //std::cout << "fuck" <<  std::endl;
    while (nodes[lastId].go[letter - 'a'] == -1) {
        //std::cout << "lastId " << lastId << " hasn't go[" << letter - 'a' << "]" << std::endl;
        nodes[lastId].go[letter - 'a'] = curId;
        lastId = nodes[lastId].link;
        //std::cout << "new LastId is " << lastId << std::endl;
    }
    //std::cout << "fuck" <<  std::endl;

    int qId = nodes[lastId].go[letter - 'a'];
    //std::cout << "qId is " << qId;
    if ((lastId == blankId) || (nodes[lastId].len + 1 == nodes[qId].len)) {
        nodes[curId].link = qId;
        lastId = curId;
        return;
    }
    nodes.push_back(nodes[qId]);
    int cloneId = nodes.size() - 1;
    nodes[cloneId].len = nodes[qId].len + 1;
    nodes[curId].link = cloneId;
    nodes[qId].link = cloneId;
    while (nodes[lastId].go[letter - 'a'] == qId) {
        nodes[lastId].go[letter - 'a'] = cloneId;
        lastId = nodes[lastId].link;
        assert(lastId!=curId);
    }
    lastId = curId;
    assert(lastId != blankId);
}

void init() {
    nodes.push_back(node);
    nodes.push_back(node);
    nodes[rootId].link = blankId;
    for (int i = 0; i < COUNTOFLETTERS; ++i) {
        nodes[blankId].go[i] = 0;
    }
}



int main() {
    std::string string;
    std::cin >> string;
    init();
    for (int i = 0; i < (int) string.length(); ++i) {
        addLetter(string[i]);
    }
    //std::cout << "audomata is done" << std::endl;

    d.resize(nodes.size());
    std::cout << dFunction(0) -(long long int)  1 << std::endl;
    for (int i = 0; i < (int) nodes.size(); ++i) {
        std::cout << "nodeId is " << i << ",node suffLink is " << nodes[i].link << std::endl;
        for (int j = 0; j < 26; ++j) {
            if (nodes[i].go[j] != -1) {
                std::cout << "\t link by " << (char) (j + 'a') << " to the node " << nodes[i].go[j] << std::endl;
            }
        }
    }
    return 0;
}
