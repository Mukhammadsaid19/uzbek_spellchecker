#include <iostream>
#include <map>
#include <fstream>
#include "soundex.h"
#include "levenshtein.h"
#include "tokenizer.h"
#include "loader.h"
#include "lemmatizer.h"
#include "LinkedList.h"
#include "permutations.h"
#include <bits/stdc++.h>
#include <regex>


using namespace std;



int main() {

    cout << "------------------------WELCOME TO UZBEK SPELLCHECKER------------------------\n";
    cout << R"(Please, enter an inflected noun lexeme in Uzbek (e.g. "insoniyatga"(to the humanity), "kitobim"(my book):)" << endl;
    string userWord;
    cin >> userWord;

    lemmatize(userWord);

    return 0;
}
