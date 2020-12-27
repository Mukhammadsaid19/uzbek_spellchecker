//
// Created by Muhammadsaid on 26.12.2020.
//

#ifndef UZBEK_SPELLCHECKER_LOADER_H
#define UZBEK_SPELLCHECKER_LOADER_H
#include<iostream>
#include<map>

void populateDict(const std::string& filename, std::multimap<std::string, std::string> &dict);
std::multimap<int, std::string> matchWordWithFile(const std::string& filename, const std::string& word);

#endif //UZBEK_SPELLCHECKER_LOADER_H
