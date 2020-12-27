//
// Created by Muhammadsaid on 26.12.2020.
//

#include "lemmatizer.h"
#include "levenshtein.h"
#include "loader.h"
#include "soundex.h"
#include "LinkedList.h"
#include "permutations.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

string getLemma(const string& lexeme);
string getAffix(const string& lexeme, int affixBorder);


/***
 * determines if the word ends with vowel
 * @param letter
 * @return
 */
bool isVowel(char letter) {
    return (letter == 'a' || letter == 'e' || letter == 'o' || letter == 'u' || letter == 'i');
}


/***
 * lemmatize returns the linked list representation of the corrected word with its affixes
 * @param word
 */
void lemmatize(const string& word) {
    multimap<string, string> lemmas;
    vector<string> wordMorphology;
    populateDict(R"(..\lexicon\lexicon.txt)", lemmas);

    multimap<int, string> sortedWords;
    std::pair<std::multimap<string, string>::iterator,std:: multimap<string, string>::iterator> collection = lemmas.equal_range(Soundex(word));

    for (auto it = collection.first; it != collection.second; it++) {
        int distance = levenshteinDistance(word, it->second);
        if (distance < 2) {
            sortedWords.insert(make_pair(distance, it->second));
        }
    }

    auto lemma = sortedWords.begin();


    int affixesDistance = word.size() - lemma->second.size();

    if (affixesDistance > 0) {
        string nullWord = getLemma(word);
        string affixWord = getAffix(word, nullWord.size());
        LinkedList<string> llist = getMorphology(affixWord);
        cout << nullWord << " -> ";
        llist.print();

    } else {
        cout << lemma->second;
    }

}

/***
 * getLemma takes in a lexeme and return a null morpheme of the lexeme
 * @param lexeme
 * @return lemma
 */
string getLemma(const string& lexeme) {
    multimap<string, string> lemmas;
    populateDict(R"(..\lexicon\lexicon.txt)", lemmas);

    multimap<int, string> lemmaWords;
    std::pair<std::multimap<string, string>::iterator,std:: multimap<string, string>::iterator> collection;

    for (auto affixIndex = lexeme.size() - 1; affixIndex > 0; affixIndex--){
        string currentWord = lexeme.substr(0, affixIndex);
        collection = lemmas.equal_range(Soundex(currentWord));
        for (auto it = collection.first; it != collection.second; it++) {
            int distance = levenshteinDistance(currentWord, it->second);
            if (distance < 2) {
                lemmaWords.insert(make_pair(distance, it->second));
            }
        }
    }
    auto lemma = lemmaWords.begin();

//    for (auto& lemm : lemmaWords){
//        cout << lemm.second << " - " << lemm.first << endl;
//    }

    auto maxLemma = lemmaWords.begin().operator++();
    int maxLength = lemma->second.size();
    for (auto affix = lemmaWords.begin(); affix != lemmaWords.end(); ++affix){
//        cout << affix->second << endl;
        if (affix->second.size() > maxLength){
            maxLength = affix->second.size();
            maxLemma = affix;
        }
    }

    lemma = lemma->second.size() > maxLemma->second.size() ? lemma : maxLemma;
    return lemma->second;
}

/***
 *
 * @param lexeme
 * @param affixBorder
 */
string getAffix(const string& lexeme, int affixBorder) {
    string affixPart = lexeme.substr(affixBorder);
    multimap<int, string> affixWords = matchWordWithFile(R"(..\noun-affixes\consonants\affixesNounEndingWithConsonant.txt)", affixPart);

    auto affix = affixWords.begin();

    return affix->second;
}

LinkedList<string> getMorphology(const string& affix) {
    vector<LinkedList<string>> mainAffixList;
    vector<string> stringAffixList;
    affixPermutations(mainAffixList);

    stringAffixList.reserve(mainAffixList.size());
    for (auto & i : mainAffixList){
        stringAffixList.push_back(i.toString());
    }

    int foundIndex = -1;
    auto it = find(stringAffixList.begin(), stringAffixList.end(), affix);
    if (it != stringAffixList.end()) {
        foundIndex = it - stringAffixList.begin();
    }

    LinkedList<string> affixLinkedList = mainAffixList[foundIndex];

    return affixLinkedList;
}