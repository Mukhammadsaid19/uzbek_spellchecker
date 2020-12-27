cmake_minimum_required(VERSION 3.17)
project(uzbek_spellchecker)

set(CMAKE_CXX_STANDARD 14)

add_executable(uzbek-spellchecker sources/main.cpp sources/soundex.cpp sources/soundex.h sources/levenshtein.h sources/levenshtein.cpp sources/tokenizer.cpp sources/tokenizer.h sources/lemmatizer.cpp sources/lemmatizer.h sources/loader.cpp sources/loader.h sources/LinkedList.cpp sources/LinkedList.h sources/permutations.cpp sources/permutations.h)