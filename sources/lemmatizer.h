//
// Created by Muhammadsaid on 26.12.2020.
//

#ifndef UZBEK_SPELLCHECKER_LEMMATIZER_H
#define UZBEK_SPELLCHECKER_LEMMATIZER_H

#include<iostream>
#include "LinkedList.h"
#include <vector>

void lemmatize(const std::string& word);
LinkedList<std::string> getMorphology(const std::string& affix);

#endif //UZBEK_SPELLCHECKER_LEMMATIZER_H
