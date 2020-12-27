//
// Created by Muhammadsaid on 26.12.2020.
//

#include "loader.h"

#include <iostream>
#include <map>
#include <fstream>
#include "soundex.h"
#include "levenshtein.h"
#include "tokenizer.h"
#include <bits/stdc++.h>
#include <regex>


using namespace std;

void populateDict(const string& filename, multimap<string, string> &dict) {

    ifstream file(filename);

    if(file.is_open()) {
        string line;

        while(getline(file, line))  {
            string soundex = Soundex(line);
            dict.insert(make_pair(soundex, line));
        }
        file.close();

    } else {
        cout << "Cannot open file: " << filename << endl;
        exit(-1);
    }
}
multimap<int, string> matchWordWithFile(const string& filename, const string& word) {
    multimap<string, string> lemmas;
    populateDict(filename, lemmas);

    multimap<int, string> sortedWords;
    std::pair<std::multimap<string, string>::iterator,std:: multimap<string, string>::iterator> collection = lemmas.equal_range(Soundex(word));

    for (auto it = collection.first; it != collection.second; it++) {
        int distance = levenshteinDistance(word, it->second);

        if (distance < 3) {
            sortedWords.insert(make_pair(distance, it->second));
        }
    }

    return sortedWords;
}