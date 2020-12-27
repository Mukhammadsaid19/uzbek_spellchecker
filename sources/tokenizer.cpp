//
// Created by Muhammadsaid on 24.12.2020.
//

#include "tokenizer.h"
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

vector<string> tokenize(const string& sentence) {
    regex re(R"([\s|,|!]+)");
    sregex_token_iterator it {sentence.begin(), sentence.end(), re, -1};
    vector<string> tokenized{it, {}};

    tokenized.erase(remove_if(tokenized.begin(), tokenized.end(), [](string const& s) {
        return s.empty();
    }), tokenized.end());

    return tokenized;
}
