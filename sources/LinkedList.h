//
// Created by Muhammadsaid on 27.12.2020.
//

#ifndef UZBEK_SPELLCHECKER_LINKEDLIST_H
#define UZBEK_SPELLCHECKER_LINKEDLIST_H

#include <iostream>
#include <utility>

template <typename T>
struct Node {
    Node<T>* next;
    T data;
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;

    LinkedList() {
        head = NULL;
    }

    void add(T value){
        if (!head) {
            head = new Node<T>;
            head->data = value;
            head->next = NULL;
        } else {
            auto temp = head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            auto* newNode = new Node<T>;
            newNode->data = value;
            newNode->next = NULL;
            temp->next = newNode;
        }
    }

    void print() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            std::cout << temp->data;
            if (temp->next != NULL){
               std::cout << " -> ";
            }
            temp = temp->next;
        }

        std::cout << std::endl;
    }

    Node<T>* contains(T x) {
        Node<T> *temp = head;
        while(temp != NULL) {
            if (temp->data == x){
                return temp;
            }
            temp = temp->next;
        }



        return NULL;
    }

    std::string toString() {
        std::string result;
        Node<T> *temp = head;
        while (temp != nullptr) {
            result.append(temp->data);
            temp = temp->next;
        }

        return result;
    }
};




#endif //UZBEK_SPELLCHECKER_LINKEDLIST_H
