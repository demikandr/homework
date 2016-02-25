//
// Created by demikandr on 11/6/15.
//

#ifndef STRINGS_AHOCORASICK_H
#define STRINGS_AHOCORASICK_H

#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>

class AhoCorasick {
    struct Node {
        bool leaf = false;
        int parentId;
        int height;
        char lastChar = 0;
        std::vector<int> links;//сразу инициализировать для root, что бы небыло бесконечного перехода по суффиксным ссылкам
        int suffixLinkId = -1;
        Node():links(26, -1) {
        }
    };
    const std::string &string;
    private:
        std::vector<Node> nodes;
        Node defaultNode;
        int _newNode(int parentId, char lastChar) {
            nodes.emplace_back();
            nodes[nodes.size()-1].parentId = parentId;
            nodes[nodes.size()-1].height = nodes[parentId].height + 1;
            nodes[nodes.size()-1].lastChar = lastChar;
            return nodes.size() - 1;
        }
        int _step(int nodeId, char letter) {
            assert(nodeId >= 0);
            if (nodes[nodeId].links[letter-'a'] != -1) {
                //std::cout << "just step in " << nodes[nodeId].links[letter-'a'] << " node" << std::endl;
                return nodes[nodeId].links[letter-'a'];
            }
            if ( (nodes[nodeId].height + 1 >= (int) string.size()) || ( (string[nodes[nodeId].height + 1] != '?') && (string[nodes[nodeId].height+1] != letter) ) ) {
                //std::cout << "step throught suffix link" << std::endl;
                return nodes[nodeId].links[letter-'a'] = _step(_getSuffixLinkId(nodeId), letter);
            }
            char nextLetter = string[nodes[nodeId].height + 1];
            //std::cout << "step in new node" << std::endl;
            return nodes[nodeId].links[letter - 'a'] = _newNode(nodeId, letter);
        }
        int _getSuffixLinkId(int nodeId) {
            //std::cout << "get suffix link for " << nodeId << std::endl;
            if (nodes[nodeId].suffixLinkId == -1) {
                assert(nodeId != 0);
                //std::cout << "init suffix link with parent help, parent is " << nodes[nodeId].parentId << std::endl;
                if (nodes[nodeId].parentId > 0) {
                    nodes[nodeId].suffixLinkId = _step(_getSuffixLinkId(nodes[nodeId].parentId),
                                                       nodes[nodeId].lastChar);
                }
                else {
                    nodes[nodeId].suffixLinkId = 0;
                }
                assert(nodes[nodeId].suffixLinkId != nodeId);
            }
            return nodes[nodeId].suffixLinkId;
        }
        int _initRoot() {
            nodes[0].height = -1;
            nodes[0].suffixLinkId = 0;
            if (string[0] == '?') {
                for (int i = 0; i < 26; ++i) {
                    nodes[0].links[i] = _newNode(0, i + 'a');
                }
            }
            else {
                for (int i = 0; i < 26; ++i) {
                    nodes[0].links[i] = 0;
                }
                nodes[0].links[string[0]-'a'] = _newNode(0, string[0]);
            }
        }
    public:
        AhoCorasick(const std::string &word, const std::string &text, int& answer):string(word), nodes(1), defaultNode() {
            _initRoot();
            //std::cout << nodes[0].links[0] << " fuck" << std::endl;
            answer = 0;
            int currentStateId = 0;
            for (int i = 0; i < (int) text.length(); ++i) {
                currentStateId = _step(currentStateId, text[i]);
                //std::cout << i << "-th height is " << nodes[currentStateId].height << std::endl;
                if (nodes[currentStateId].height == (int) word.length() - 1) {
                    ++answer;

                }
            }
        }
};


#endif //STRINGS_AHOCORASICK_H
