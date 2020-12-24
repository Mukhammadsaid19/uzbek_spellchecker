//
// Created by navruz on 12/23/2020.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int levenshteinDistance(string a, string b) {

    transform(a.begin(), a.end(), a.begin(), [](unsigned char c){ return std::tolower(c); });
    transform(b.begin(), b.end(), b.begin(), [](unsigned char c){ return std::tolower(c); });

    int costs[b.size() + 1];

    for (int j = 0; j < sizeof(costs)/sizeof(int); j++) {
        costs[j] = j;
    }

    for (int i = 1; i <= a.size(); i++) {
        costs[0] = i;
        int nw = i - 1;

        for (int j = 1; j <= b.size(); j++) {
            int cj = min(1 + min(costs[j], costs[j - 1]), a[i - 1] == b[j - 1] ? nw : nw + 1);
            nw = costs[j];
            costs[j] = cj;
        }
    }

    return costs[b.size()];
}




