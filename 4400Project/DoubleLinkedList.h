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
    LinkedListNode<T>* prev;

    LinkedListNode(string key, string name) : LinkedList<T>(key, name) {
        next = NULL;
        prev = NULL;
    }

    LinkedListNode<T>* nodeSortTo(string sortBy) {
        LinkedListNode<T>* newList = new LinkedListNode<T>(sortBy, this->name);
        newList->next = this->next;
        newList->prev = this->prev;

        Node<T> *temp = this->head;

        while (temp != NULL) {
            newList->insertProduct(temp->product);
            temp = temp->next;
        }

        return newList;
    }

    Node<T>* getHead() {
        return this->head;
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

        // Otherwise, add new node at the end
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
        return;

    }

    T* getFirst() { return first; }
    T* getLast() { return last; }

};



struct CategoryDoubleLinkedList : public DoubleLinkedList<LinkedListNode<float> > {

    // Updates the first and last node at the same time, this ensures the first and last aren't pointing to
    // separate lists
    void setFirstAndLast(LinkedListNode<float>* f, LinkedListNode<float>* l) {
        this->first = f;
        this->last = l;
    }

    // Linear search function (since this is not an ordered list)
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

    // get category reference from catNo
    LinkedListNode<float>* getCategory(int catNo) {
        LinkedListNode<float>* category = this->first;
        
        for (int i = 1; i < 4; i++)
        {
            if(i == catNo){
                break;
            } else {
                category = category->next;
            }
        }
        return category;
    }

    // This changes the sort method of the LinkedLists stored inside the CategoryDoubleLinkedList
    void sortTo(string key) {
        LinkedListNode<float>* category = this->first;
        LinkedListNode<float>* prev = NULL;
        LinkedListNode<float>* newFirst = NULL;


        while (category != NULL) {
            category = category->nodeSortTo(key);

            // Since sortTo reassigns the pointer to a new object, the referencing needs to be updated
            if (prev != NULL) {
                prev->next = category;
                category->prev = prev;
            }


                // Special case: this is the first LinkedListNode sorting differently.
                // in this case the head of the catalogue DLL need to be set to this. The head is reserved
                // the first and last node can be updated at the same time after the loop. This ensures no
                // partial switch.
            else {
                newFirst = category;
            }

            // Increment along
            prev = category;
            category = category->next;
        }

        // Update the catalogue, so it is linked to the new (resorted) nodes
        this->setFirstAndLast(newFirst, prev);

        return;
    }


};

#endif //JSONPARSING_DOUBLELINKEDLIST_H
