//
// Created by demikandr on 11/20/15.
//

#ifndef STRINGS_UKOKOKONEN_H
#define STRINGS_UKOKOKONEN_H


class Ukokokonen {
private:
    static const int rootId = 0, blankId = 1, countOfLetters = 28, MAXHEIGHT = 1000000000;
    int firstStringLength, secondStringLength, maxLCSHeight, maxLCSId;
    struct Node {
        int suffixLinkId, parentId, l, r, length;
        std::vector<int> links;

        Node() : suffixLinkId(-1), parentId(-1), l(-1), r(-1), length(0), links(countOfLetters, -1) { };
    };

    std::vector<Node> nodes;
    const std::string &string;

    void init() {
        nodes.resize(2);
        nodes[rootId].suffixLinkId = blankId;
        for (int i = 0; i < countOfLetters; ++i) {
            nodes[blankId].links[i] = rootId;
        }
        nodes[blankId].suffixLinkId = rootId;


    }


    Node node;

    void addSon(int parentId, char currentChar, int currentPositionInString) {
        //std::cout << "addSon from id" << parentId << " and char  " << currentChar << std::endl;
        assert(nodes[parentId].links[currentChar - 'a'] == -1);
        nodes[parentId].links[currentChar - 'a'] = nodes.size();
        nodes.push_back(node);
        Node &lastNode = nodes[nodes.size() - 1];
        lastNode.parentId = parentId;
        lastNode.l = currentPositionInString;
        lastNode.r = string.length() - 1;
        lastNode.length = lastNode.r - lastNode.l;
        assert(lastNode.length >= 0);
    }


    void split(int &spId, int &spPos) {
        assert(spId > 1);
        assert(spPos >= 0);
        assert(spPos <= nodes[spId].length);
        //std::cout << "split from id" << spId << " and pos " << spPos << std::endl;
        assert(spId >= 0);
        assert(spPos >= 0);
        nodes.push_back(node);
        Node &lastNode = nodes[nodes.size() - 1];
        lastNode.l = nodes[spId].l;
        lastNode.r = lastNode.l + spPos;
        lastNode.parentId = nodes[spId].parentId;
        lastNode.length = lastNode.r - lastNode.l;
        nodes[spId].l += spPos + 1;
        lastNode.links[string[nodes[spId].l] - 'a'] = spId;
        nodes[spId].length -= spPos + 1;
        assert(nodes[spId].length == nodes[spId].r - nodes[spId].l);
        nodes[spId].parentId = nodes.size() - 1;
        spId = nodes.size() - 1;
        spPos = lastNode.length;
        nodes[lastNode.parentId].links[string[lastNode.l] - 'a'] = nodes.size() - 1;
    }

    bool go(int &spId, int &spPos, int currentChar, int currentPosInString) {
        //std::cout << "go from id" << spId << " and pos " << spPos << std::endl;
        assert(spId >= 0);
        assert(spPos >= 0);
        assert(spPos <= nodes[spId].length);
        if (spPos == nodes[spId].length) {
            if (nodes[spId].links[currentChar - 'a'] == -1) {
                addSon(spId, currentChar, currentPosInString);
                return false;
            }
            else {
                spId = nodes[spId].links[currentChar - 'a'];
                spPos = 0;
                return true;
            }
        }
        else {
            assert(nodes[spId].l + spPos + 1 < string.length());
            //std::cout << "do i realy need to split " << spId << "-th node in " << spPos << " pos with next char " << string[nodes[spId].l + spPos + 1] << std::endl;
            if (string[nodes[spId].l + spPos + 1] == (currentChar)) {
                ++spPos;
                return true;
            }
            else {
                split(spId, spPos);// split change spId and spPos to highest edge
                addSon(spId, currentChar, currentPosInString);
                return false;
            }
        }
    }

    void goSuffLink(int &spId, int &spPos) {
        //std::cout << "goSuffLink from id" << spId << " and pos " << spPos << std::endl;
        assert(spId >= 0);
        assert(spPos >= 0);
        assert(spPos <= nodes[spId].length);
        if (spPos == nodes[spId].length) {
            if (nodes[spId].suffixLinkId != -1) {
                spId = nodes[spId].suffixLinkId;
                spPos = nodes[spId].length;
                return;
            }
            int l = nodes[spId].l;
            int r = nodes[spId].r;
            int height = nodes[spId].length;
            int currentId = nodes[spId].parentId;
            assert((currentId >= 0) && (1==1));
            currentId = nodes[currentId].suffixLinkId;
            assert(currentId >= 0);
            currentId = nodes[currentId].links[string[l] - 'a'];
            while (nodes[currentId].length < height) {
                height -= nodes[currentId].length + 1;
                l += nodes[currentId].length + 1;
                currentId = nodes[currentId].links[string[l] - 'a'];
            }
            if (nodes[currentId].length > height) {
                split(currentId, height);
            }
            spPos = height;
            nodes[spId].suffixLinkId = currentId;
            spId = currentId;

        }
        else {
            assert(false);
            /*int l = nodes[spId].l;
            int r = l + spPos;
            spId = nodes[spId].parentId;
            int height = spPos + 1;
            spId = nodes[spId].suffixLinkId;
            assert(spId >= 0);
            --height, ++l;
            while (height > 0) {
                spId = nodes[spId].links[string[l] - 'a'];
                if (nodes[spId].length + 1 < height) {
                    height -= nodes[spId].length + 1;
                    l += nodes[spId].length + 1;
                }
                else {
                    spPos = height - 1;
                    height = 0;
                }
            }*/
        }
    }

    void makeSuffixTree(const std::string string) {
        int spId = rootId;
        int spPos = 0;
        for (int i = 0; i < (int) string.size(); ++i) {
            //std::cout << "\tADD " << i << "-th char(" << string[i] << ")" << std::endl;
            char currentChar = string[i];
            while (!go(spId, spPos, currentChar, i)) {
                goSuffLink(spId, spPos);
                //std::cout << "change spId to " << spId << " and spPos to " << spPos << std::endl;
            }
        }
    }
    int dfs(int nodeId) {
        //std::cout << " in " << nodeId << "-th node" << std::endl;

        int result = nodes[nodeId].length + 1;
        if (nodeId == 0) {
            --result;
        }
        for (int i = 0; i < countOfLetters; ++i) {
            if (nodes[nodeId].links[i] != -1) {
                result+=dfs(nodes[nodeId].links[i]);
            }
        }
        return result;
        //std::cout << "closestEndHeight is " << closestEndHeight <<", farestEndHeight " << farestEndHeight << ", height is " << height << std::endl;
        //std::cout << "closestEndHeight is " << closestEndHeight <<", farestEndHeight " << farestEndHeight << std::endl;
        //std::cout << " out of " << nodeId << "-th node" << std::endl;
    }

    std::string getString(int nodeId) {
        std::string tString;
        //std::cout << "getString from id " << nodeId << std::endl;
        while (nodeId != 0) {
            //std::cout << "l is " << nodes[nodeId].l << ", r is " << nodes[nodeId].r << std::endl;
            for (int i = nodes[nodeId].r; i >= nodes[nodeId].l; --i) {
                tString += string[i];
            }
            nodeId = nodes[nodeId].parentId;
            //std::cout <<"go to id " << nodeId << std::endl;
        }
        return tString;
    }
public:
    Ukokokonen(const std::string& string): string(string) {
        init();
        makeSuffixTree(string);
    }
    int getCountOfSubstrings(int firstStringLength) {
        //std::cout << "**********Lets find LCS!!!***********" << std::endl;
        int t1, t2;
        maxLCSHeight = -1;
        Ukokokonen::firstStringLength = firstStringLength;
        secondStringLength = string.length() - firstStringLength - 2;
        return dfs(rootId);
    }
};


#endif //STRINGS_UKOKOKONEN_H
