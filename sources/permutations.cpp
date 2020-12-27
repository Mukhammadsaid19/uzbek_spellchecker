//
// Created by Muhammadsaid on 27.12.2020.
//

#include "permutations.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "LinkedList.h"

using namespace std;

std::vector<string> a = {"im",
                         "ing",
                         "i",
                         "imiz",
                         "ingiz",
                         "m",
                         "ng",
                         "ngiz",
                         "lari",
                         "ning",
                         "ni",
                         "da",
                         "ga",
                         "dan",
                         "man",
                         "san",
                         "miz",
                         "sizlar",
                         "mish",
                         "ov",
                         "yov",
                         "mi",
                         "-a",
                         "-ya",
                         "mikan",
                         "-chi",
                         "mas",
                         "siz",
                         "lar",
                         "dir",
                         "kan",
                         "jon",
                         "xon",
                         "chak",
                         "choq",
                         "kay",
                         "gina",
                         "niki",
                         "dagi",
                         "gacha",
                         "ligi",
                         "cha",
                         "chalik",
                         "dek",
                         "day",
                         "-ku",
                         "-da"};

vector<string> combination;



void pretty_print(const vector<string>& v, vector<LinkedList<string>>& mainAffixList) {
    LinkedList<string> tempList;
    static int count = 0;
    for (const string& i : v) {
        tempList.add(i);
    }
    mainAffixList.push_back(tempList);
}

void go(int offset, int k, vector<LinkedList<string>>& mainAffixList) {
    if (k == 0) {
        pretty_print(combination, mainAffixList);
        return;
    }
    for (int i = offset; i <= a.size() - k; ++i) {
        combination.push_back(a[i]);
        go(i+1, k-1, mainAffixList);
        combination.pop_back();
    }
}

void affixPermutations(vector<LinkedList<string>>& mainAffixList) {
    go(0, 2, mainAffixList);

    for(auto & i : a) {
        LinkedList<string> temp;
        temp.add(i);
        mainAffixList.push_back(temp);
    }
}



