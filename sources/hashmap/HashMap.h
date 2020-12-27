//
// Created by navruz on 12/26/2020.
//

#ifndef UZBEK_SPELLCHECKER_HASHMAP_H
#define UZBEK_SPELLCHECKER_HASHMAP_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "HashNode.h"



template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
private:
    HashNode <K, V> **table;
    F hashFunc;
    std::list<int> inds; // just for outputing (can be removed later)
    int v_size;
public:
    std::vector<int> indices;
    class iterator;

public:

    iterator begin() {
        return iterator(table[inds.front()], table, indices);
    }
    iterator end() {
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *node = table[inds.back()];

        while(node != NULL) {
            prev = node;
            node = node->getNext();
        }
        return iterator(node, table, indices);
    }

public:

    HashMap() {
        v_size = 0;
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != NULL) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        delete [] table;
    }

    void insert(std::pair<K, V> pair) {
        unsigned long hashValue = hashFunc(pair.first);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        if(find(pair))
            return;

        while (entry != NULL) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(pair.first, pair.second);
            if (prev == NULL) {
                // if it is the first element with such key
                table[hashValue] = entry;

                indices.push_back(hashValue);
                inds.push_back(hashValue);

                entry->setPos(v_size);
                v_size++;
            } else {
                entry->setPos(prev->getPos());
                prev->setNext(entry);
            }
        }

    }

    bool find(std::pair<K, V> pair) {
        unsigned long hashValue = hashFunc(pair.first);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == pair.first && entry->getValue() == pair.second) {
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    // returns the number of elements deleted
    int erase(const K &key) {
        int deletedN = 0;

        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        table[hashValue] = NULL;

        if(entry != NULL) {
            indices.erase(indices.begin() + entry->getPos());
        }

        while (entry != NULL) {
            inds.remove(hashValue);

            v_size--;

            HashNode<K, V> *temp = entry;
            entry = entry->getNext();
            delete temp;
        }

        return deletedN;
    }

    void display() {
        for (int index: inds) {
            HashNode<K, V> *entry = table[index];

            while(entry != NULL) {
                std::cout << "(" << entry->getKey() << ": " << entry->getValue() << ": " << entry->getPos() << ") -> ";
                entry = entry->getNext();
            }
            std::cout << "NULL" << std::endl;
        }
    }

    std::pair<HashMap<K, V, F>::iterator, HashMap<K, V, F>::iterator> equal_range(const K &key) {
        int hashValue = hashFunc(key);
        HashNode<K, V> *node = table[hashValue];
        if (node != NULL) {
            iterator it1(node, table, indices);
            iterator it2(NULL, table, indices);
            return std::make_pair(it1, it2);
        } else {
            return std::make_pair(iterator(NULL, table, indices), iterator(NULL, table, indices));
        }
    }
};


template <typename K, typename V, typename F>
class HashMap<K, V, F>::iterator {
private:
    HashNode<K, V> **table;
    HashNode<K, V> *node;
    F hashFunc;
    std::vector<int> &indices;
public:
    iterator(HashNode<K, V> *node, HashNode<K, V> **table, std::vector<int> &indices) : table(table), node(node), indices(indices) {}

    iterator &operator++(int) {
        if (node->getNext() != NULL) {
            node = node->getNext();
        } else {
            if ((node->getPos() + 1) <= indices.size()) {
                int nextHValue = indices[node->getPos() + 1];
                node = table[nextHValue];
            }
        }
        return *this;
    }

    iterator &operator++() {
        if (node->getNext() != NULL) {
            node = node->getNext();
        } else {
            if ((node->getPos() + 1) <= indices.size()) {
                int nextHValue = indices[node->getPos() + 1];
                node = table[nextHValue];
            }
        }
        return *this;
    }

    std::pair<K, V> operator*() {
        return std::make_pair(node->getKey(), node->getValue());
    }

    bool operator!=(const iterator &other) {
        return node != other.node;
    }

    HashNode<K, V> *operator->() {
        return node;
    }


};


#endif //UZBEK_SPELLCHECKER_HASHMAP_H
