//
// Created by Malcolm on 2022-07-31.
//

#ifndef JSONPARSING_DOUBLELINKEDLIST_H
#define JSONPARSING_DOUBLELINKEDLIST_H
#include <iostream>

using namespace std;

// This is a linked list but acts as a node in the DLL
template<class T>
struct LinkedListNode : public LinkedList<T> {
    LinkedListNode<T>* next;

    LinkedListNode(string key, string name) : LinkedList<T>(key, name) {
        next = NULL;
    }
};



template<class T>
struct DoubleLinkedList {
protected:
    T* first;
    T* last;

public:

    DoubleLinkedList() {
        first = NULL;
        last = NULL;
    }

    void push(T* newNode) {
        // Special case: empty DLL
        if (first == NULL) {
            first = newNode;
            last = newNode;
            return;
        }

        // Otherwise, make the new node the next of the last node and update the last referencing
        last->next = newNode;
        last = newNode;
        return;

    }

    T* getFirst() { return first; }
    T* getLast() { return last; }

};



struct CategoryDoubleLinkedList : public DoubleLinkedList<LinkedListNode<float> > {

    LinkedListNode<float>* search(string category) {
        // Special case: empty DLL
        if (first == NULL) {
            return NULL;
        }


        // Get temporary traversal node
        LinkedListNode<float>* temp = first;

        // Go through all nodes in this linked list looking for a match
        while (temp != NULL) {
            // When a matching category is found, return it
            if (category == temp->name) {
                return temp;
            }
            temp = temp->next;
        }



        // If no match is found, return NULL
        return NULL;
    }


    // Print function
    void displayProducts() {

        LinkedListNode<float>* category = this->first;

        while (category != NULL) {
            cout << "Category: " << category->name << endl;

            category->displayProducts();

            category = category->next;

            cout << endl;
        }

        return;
    }


};

#endif //JSONPARSING_DOUBLELINKEDLIST_H
