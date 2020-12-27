#include <iostream>
#include <map>
#include <fstream>
#include "soundex.h"
#include "levenshtein.h"
#include "map/HashMap.h"

using namespace std;

// ================== For Testing HashMap ===================

struct MyKeyHash {
    unsigned long operator()(const int &k) const { return k % 100; }
};


// ==========================================================

void populateDict(string filename, multimap<string, string> &dict) {

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

int main() {

    multimap<string, string> dict;
    multimap<string, string> affixes;

    populateDict(R"(C:\Users\navruz\CLionProjects\uzbek-spellchecker\lexicon.txt)", dict);
    populateDict(R"(C:\Users\navruz\CLionProjects\uzbek-spellchecker\oneElementAffix.txt)", affixes);
    populateDict(R"(C:\Users\navruz\CLionProjects\uzbek-spellchecker\twoElementsAffixes.txt)", affixes);

    string word = "daftaringizmikan";

    multimap<int, string> sortedWords;

    bool isFound = false;
    string temp = word;
    int affixBoundary;

    for (affixBoundary = temp.length() - 1; affixBoundary >= 0 && !isFound; affixBoundary--) {

        temp = temp.substr(0, affixBoundary);

        pair<multimap<string, string>::iterator, multimap<string, string>::iterator> its = dict.equal_range(Soundex(temp));

        for (auto it = its.first; it != its.second; it++) {
            int distance = levenshteinDistance(temp, it->second);

            if (distance == 0) {
                sortedWords.insert(make_pair(distance, it->second));
                isFound = true;
            }
        }

    }


    string affixPart = word.substr(affixBoundary + 1);

    auto its2 = affixes.equal_range(Soundex(affixPart));

    multimap<int, string> sortedAffixes;

    for (auto it = its2.first; it != its2.second; it++) {
        int distance = levenshteinDistance(affixPart, it->second);

        if (distance < 4) {
            sortedAffixes.insert(make_pair(distance, it->second));
        }
    }

    cout << "Current entry: " + word << endl;
    cout << "\nMatching morphemes: " << endl;


    for (auto it = sortedAffixes.begin(); it != sortedAffixes.end(); it++) {
        cout << it->second << " - " << it->first << endl;
    }

    cout << "================================  Testing MultiMap =================================== " << endl;

    HashMap<int, string, MyKeyHash> map;

    map.insert(make_pair(34, "hello"));
    map.insert(make_pair(117, "amigo"));
    map.insert(make_pair(57, "salut"));
    map.insert(make_pair(67, "blank"));
    map.insert(make_pair(117, "salom"));
    map.insert(make_pair(67, "morning"));
    map.insert(make_pair(67, "juicy"));
    map.insert(make_pair(57, "salut"));

    map.display();

    cout  << "***************** Iterating through Map (not sorted) ***********************" << endl;

    for (HashMap<int, string, MyKeyHash>::iterator it1 = map.begin(); it1 != map.end(); it1++) {
       cout << it1->getKey() << ": " << it1->getValue() << endl;
    }

    cout << "************************ Testing equal_range(key) ****************************" << endl;

    pair<HashMap<int, string, MyKeyHash>::iterator, HashMap<int, string, MyKeyHash>::iterator> itss = map.equal_range(67);

    for (HashMap<int, string, MyKeyHash>::iterator it1 = itss.first; it1 != itss.second; it1++) {
        cout << it1->getKey() << ": " << it1->getValue() << endl;
    }

    cout << "*****************************************************************************" << endl;


    HashMap<int, string, MyKeyHash>::iterator it = map.begin();
    cout << it->getKey() << ": " << it->getValue() << endl;
    it++;


    cout << "After deleting elements with key 67:" << endl;

    map.erase(67);
    map.display();

    return 0;
}
