cmake_minimum_required(VERSION 3.17)
project(uzbek_spellchecker)

set(CMAKE_CXX_STANDARD 14)

add_executable(uzbek-spellchecker sources/main.cpp sources/soundex.cpp sources/soundex.h sources/levenshtein.h sources/levenshtein.cpp)