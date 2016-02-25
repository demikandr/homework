//
// Created by demikandr on 10/28/15.
//

#ifndef STRINGS_PZFUCNCTIONS_H
#define STRINGS_PZFUCNCTIONS_H

#include <vector>
#include <string>
#include <memory>
#include <assert.h>


std::vector<int> prefixFunction(const std::string& string){ //done
    int n = (int) string.length();
    std::vector<int> prefixFunction (n);
    for (int i = 1; i < n; ++i) {
        int j = prefixFunction[i-1];
        while ((j > 0) && (string[i] != string[j])) {
            j = prefixFunction[j - 1];
        }
        if (string[i] == string[j])  {
            ++j;
        }
        prefixFunction[i] = j;
    }
    return prefixFunction;
}


std::vector<int> zFunction(const std::string& string) {//done
    int n = (int) string.length();
    std::vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while ((i + z[i] < n) && (string[z[i]] == string[i + z[i]])) {
            ++z[i];
        }
        if (i+z[i]-1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

std::string zToString(const std::vector<int>& z) { //done
    int a, n;
    n = (int) z.size();
    std::vector<std::vector<char> > forbidden(n+1);

    std::string string;
    string.resize(n);
    for (int i = 0; i < n; ++i) {
        string[i]='#';
    }
    string[0] = 'a';

    std::vector<int> tForbidden(28);
    //std::cout << string[0] << std::endl;

    for (int i = 1, l = 0, r = 0; i < n; ++i) {

        for (l = std::max(l, i); l < i + z[i]; ++l) {
            string[l] = string[l-i];
        }
        // std::cout << "add to forbidden " << i+z[i] << ' ' << string[z[i]] << std::endl;
        forbidden[i+z[i]].push_back(string[z[i]]);
        //std::cout << string[i] << std::endl;
        if (string[i] == '#') {
            for (int j = 0; j < (int) forbidden[i].size(); ++j) {
                tForbidden[forbidden[i][j] - 'a'] = i;
            }
            for (int j = 0; j < 28; ++j) {
                if (tForbidden[j] != i) {
                    string[i] = j + 'a';
                    break;
                }
                assert(j != 26);
            }


        }
        //std::cout << string[i] << std::endl;

    }
    //assert(zFunction(string) == z);
    return string;

}

std::vector<int> prefixToZ(const std::vector<int>& prefixFunction) { // done
    return z(prefixToString(prefixFunction));
}

std::vector<int> zToPrefix(const std::vector<int>& z) {
    int n = (int) z.size();
    std::vector <int> prefixFunction(n);
    for (int i = 0, j = 0;j < n; ++i) {
        int r = i + z[i]-1;
        for (; j <= r; j++) {
            prefixFunction[j] = j - i+1;
        }
    }
    return prefixFunction;
}



std::string prefixToString(const std::vector<int>& prefixFunction) {
    int n,a;
    //std::cout << "fuck";
    std::string string;
    string.resize(prefixFunction.size());
    string[0]='a';
    char lastChar='a';
    std::vector<int> forbidden(33);
    assert(prefixFunction.size()<100);
    for (int i = 1 ; i < (int) prefixFunction.size(); ++i) {
        if (prefixFunction[i] > 0) {
            string[i] = string[prefixFunction[i] - 1];
        }
        else {
            int j = prefixFunction[i - 1];
            while (j != 0) {
                forbidden[string[j] - 'a'] = i;
                j = prefixFunction[j - 1];

            }
            forbidden[string[0] - 'a'] = i;

            for (int j = 0; j < 33; ++j) {
                if (forbidden[j] != i) {
                    string[i] = j + 'a';
                    assert(string[i]<='z');
                    break;
                }
            }
        }
    }
    //assert(::prefixFunction(string)==prefixFunction);

    return string;

}


#endif //STRINGS_PZFUCNCTIONS_H
