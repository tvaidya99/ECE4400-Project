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

    LinkedListNode<T>* nodeSortTo(string sortBy) {
        LinkedListNode<T>* newList = new LinkedListNode<T>(sortBy, this->name);
        newList->next = this->next;

        Node<T> *temp = this->head;

        while (temp != NULL) {
            newList->insertProduct(temp->product);
            temp = temp->next;
        }

        return newList;
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

    void setFirstAndLast(LinkedListNode<float>* f, LinkedListNode<float>* l) {
        this->first = f;
        this->last = l;
    }

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

        // Print specific category product 
    void displaybyCatProducts(int catNo) {

        LinkedListNode<float>* category = this->first;

        switch (catNo)
        {
        case (1):
            while (category != NULL) {
                if (category->name == "dairy")
                {
                    category->displayProducts();

                    category = category->next;
                    cout << endl;
                }
                else 
                {
                    category = category->next;
                }
            }
            break;
        case (2):
            while (category != NULL) {
                if (category->name == "meat")
                {
                    category->displayProducts();

                    category = category->next;
                    cout << endl;
                }
                else
                {
                    category = category->next;
                }
            }
            break;
        case (3):
            while (category != NULL) {
                if (category->name == "produce")
                {
                    category->displayProducts();

                    category = category->next;
                    cout << endl;
                }
                else
                {
                    category = category->next;
                }
            }
            break;
        default:
            break;
        }

        return;
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
