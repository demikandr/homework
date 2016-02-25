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
class AhoCorasick {
    private:
        struct Node {
            long long int parentId;
            std::vector<long long int> height;
            char lastChar;
            bool leaf;
            std::vector<long long int> links;
            //сразу инициализировать для root, что бы небыло бесконечного перехода по суффиксным ссылкам
            long long int suffixLinkId;

            Node() : lastChar(0), leaf(false), links(28, -1), suffixLinkId(-1) {
            }
        };

        std::vector<Node> nodes;
        Node node;
        std::vector<long long int> marks;
        long long int wordSize, substrCount;


        void newNode(long long int parentId, long long int currentChar) {
            nodes.push_back(node);
            Node &node = nodes[nodes.size() - 1];
            node.parentId = parentId;
            node.lastChar = currentChar;
        }

        long long int addChar(long long int currentState, char currentChar) {
            if (nodes[currentState].links[currentChar - 'a'] == -1) {
                newNode(currentState, currentChar);
                nodes[currentState].links[currentChar - 'a'] = nodes.size() - 1;
            }
            return nodes[currentState].links[currentChar - 'a'];
        }

        void addWord(const std::string currentString, long long int height) {
            ++substrCount;
            assert(currentString.length() > 0);
            long long int currentState = 0;
            for (long long int j = 0; j < currentString.length(); ++j) {
                currentState = addChar(currentState, currentString[j]);
            }
            nodes[currentState].leaf = true;
            nodes[currentState].height.push_back(height);
        }

        void initRoot() {
            for (long long int i = 0; i < 26; ++i) {
                if (nodes[0].links[i] == -1) {
                    nodes[0].links[i] = 0;
                }
            }
            nodes[0].suffixLinkId = 0;
        }

        void makeBor(const std::string &word) {
            std::string tempString;
            long long int i;
            for (i = 0; i < (long long int) word.length(); ++i) {
                if (word[i] != '?') {
                    assert((word[i] >= 'a') && (word[i] <= 'z'));
                    tempString += word[i];
                }
                else {
                    if (tempString.length() > 0) {
                        addWord(tempString, i - 1);
                        tempString = "";
                    }
                }
            }
            if (tempString.length() > 0) {
                addWord(tempString, i - 1);
                tempString = "";
            }
            initRoot();

        }

        long long int getSuffixLink(long long int nodeId);

        long long int step(long long int nodeId, char currentChar) {
            assert((currentChar >= 'a') && (currentChar <= 'z'));
            if (nodes[nodeId].links[currentChar - 'a'] != -1) {
                return nodes[nodeId].links[currentChar - 'a'];
            }
            return step(getSuffixLink(nodeId), currentChar);
        }

        void addMark(long long int nodeId, long long int pos) {
            assert(nodeId >= 0);
            if (nodeId == 0) {
                return;
            }
            assert(nodeId > 0);
            addMark(getGoLink(nodeId), pos);
            // std::cout << "add mark " << nodes[nodeId].leaf << " to " << pos-nodes[nodeId].height << " from node " << nodeId << std::endl;
            for (int i = 0; i < nodes[nodeId].height.size(); ++i) {
                if ((pos - nodes[nodeId].height[i] >= 0)) {

                    //std::cout << "add mark " << nodes[nodeId].leaf << " to " << pos-nodes[nodeId].height << " from node " << nodeId << std::endl;
                    marks[pos - nodes[nodeId].height[i]] += 1;
                }
            }
        }

        long long int getSuffixLink(long long int nodeId) {
            assert(nodeId >= 0);
            if (nodes[nodeId].suffixLinkId == -1) {
                assert(nodeId > 0);
                if (nodes[nodeId].parentId == 0) {
                    nodes[nodeId].suffixLinkId = 0;
                }
                else {
                    nodes[nodeId].suffixLinkId = step(getSuffixLink(nodes[nodeId].parentId), nodes[nodeId].lastChar);
                }
            }
            assert(nodes[nodeId].suffixLinkId >= 0);
            return nodes[nodeId].suffixLinkId;
        }

        long long int getGoLink(long long int nodeId) {
            assert(nodeId >= 0);
            if (nodes[nodeId].leaf == true) {
                return nodeId;
            }
            if (nodes[nodeId].goLinkId == -1) {
                if (nodes[nodeId].suffixLinkId == -1) {
                    assert(nodeId > 0);
                    if (nodes[nodeId].parentId == 0) {
                        nodes[nodeId].suffixLinkId = 0;
                    }
                    else {
                        nodes[nodeId].suffixLinkId = step(getSuffixLink(nodes[nodeId].parentId),
                                                          nodes[nodeId].lastChar);
                    }
                }
                nodes[nodeId].goLinkId = getGoLink(nodes[nodeId].suffixLinkId);
            }
            assert(nodes[nodeId].suffixLinkId >= 0);
            return nodes[nodeId].goLinkId;
        }


    public:
        void printEntries() {
            for (long long int i = 0; i <= (long long int) marks.size() - wordSize; ++i) {
                if (marks[i] == substrCount) {
                    std::cout << i << ' ';
                }
            }
        }
        AhoCorasick(const std::string& word, const std::string& text) {
            assert(word.length()>0);
            //std::cout << "read word and text" << std::endl;
            wordSize = word.length();
            nodes.push_back(node);
            marks.resize(text.length());
            nodes[0].leaf = true;
            long long int answer;
            makeBor(word);
            long long int currentState = 0;
            for (long long int i = 0; i < text.length(); ++i) {
                currentState = step(currentState, text[i]);
                //std::cout << i << "-th step to " << currentState << " state" << std::endl;
                addMark(currentState, i);
            }
        }

};

