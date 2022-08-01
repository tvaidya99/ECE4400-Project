//
// Created by Malcolm on 2022-07-31.
//

#ifndef JSONPARSING_JSONPARSER_H
#define JSONPARSING_JSONPARSER_H

#include <iostream>
#include <fstream>
#include <string>

#include "DoubleLinkedList.h"
using namespace std;



// Setting up static string trimming with in-build string methods.
const string REMOVE = " \n\t\":},";

string trim(string s, string remove = REMOVE) {
    size_t index = s.find_first_not_of(remove);

    // Special case: string is only whitespace
    if (index == string::npos)
        return "";

    // Update string now that the front is trimmed
    s = s.substr(index);

    // Trim the end of the string
    index = s.find_last_not_of(remove);
    s = s.substr(0, index+1);

    return s;
}






// Item Node to hold all item information
struct ItemNode {
    string name;
    string category;
    int count;
    float price;
    int expiry;
    ItemNode* next;

    ItemNode() {
        name = category = "";
        expiry = count = 0;
        price = 0.0;
        next = NULL;
    }

    void print() {
        cout << "Name: " << name << ", Category: " << category << ", Price: $" << price << ", expiry: " << expiry << ", count: " << count << endl;
        return;
    }
};



// Queue to store Item Nodes
template <class T>
class Queue {
protected:
    T* first;
    T* last;

public:
    Queue() {
        first = NULL;
        last = NULL;
    }

    void enqueue(T* i) {
        // Check that i is not NULL
        if (i == NULL)
            return;

        // Special case: First item
        if (first == NULL) {
            first = i;
            last = i;
            return;
        }

        // Otherwise, insert to last
        last->next = i;
        last = i;
        return;
    }

    T* dequeue() {
        // Special case: empty queue
        if (first == NULL) {
            return NULL;
        }

        T* temp = first;

        // Special case: 1 item in queue
        if (first == last) {
            first = NULL;
            last = NULL;
            return temp;
        }

        // Otherwise move first to the next node, remove the link and return it
        first = temp->next;
        temp->next = NULL;
        return temp;
    }

    // Function for debug testing to print out queues
    T* getFirst() {
        return first;
    }

};



template <class T>
struct CategoryQueue : public Queue<T> {
    CategoryQueue<T>* next;
    string category;

    CategoryQueue(string category) : category(category), Queue<T>() {
        next = NULL;
    }
};



template<class T>
struct OuterCategoryQueue : public Queue<CategoryQueue<T>> {
    CategoryQueue<T>* search(string category) {
        CategoryQueue<T>* temp = this->first;

        // Special case: This queue is empty
        if (temp == NULL)
            return NULL;

        // Cycle through the queue until there is a match
        while (temp != NULL) {
            if (temp->category == category) {
                return temp;
            }
            temp = temp->next;
        }

        // Special case: No match found
        return NULL;
    }
};






// Controller class
class JSONInterface {
private:

    Queue<ItemNode>* unsortedData;
    CategoryDoubleLinkedList* sorted;


    // Reads all the data and returns the raw text as a string
    string getRawData(string filename) {

        // Setup variables to open file and store data
        ifstream fileHandler;
        fileHandler.open(filename);
        string allData;
        string thisData;

        // If the file opens successfully, store the full text in allData
        if (fileHandler.is_open()) {
            fileHandler >> thisData;
            allData = thisData;
            while (!fileHandler.eof()) {
                fileHandler >> thisData;
                allData += " " + thisData;
            }
        }

        return allData;

    }

    Queue<ItemNode>* parseData(string allData) {
        // QUEUE SETUP
        Queue<ItemNode>* items = new Queue<ItemNode>();
        ItemNode* temp = NULL;


        // PARSING
        bool lookingForKey = true;
        bool recording = false;
        char c;
        string key;
        string val;

        for (int i = 0; i < allData.size(); i++) {

            // c is the current char at position i in the data
            c = allData.at(i);

            // Handle recording
            if (recording) {
                if (lookingForKey) {
                    key += c;
                }
                else if (!lookingForKey) {
                    val += c;
                }
            }



            // Handle key edge cases
            if (lookingForKey) {

                // If a quote is discovered, then:
                if (c == '"') {

                    // Start recording if not already recording
                    if (!recording) {
                        recording = true;
                        key = "";
                        continue;
                    }
                        // Stop recording if already recording, and switch to searching for value
                    else if (recording) {
                        lookingForKey = false;
                        val = "";
                        continue;
                    }

                }



            }



                // Handle value edge cases
            else {
                if (recording && c == ',') {
                    recording = false;
                    lookingForKey = true;

                    // Handle when key and value are both found
                    key = trim(key);
                    val = trim(val);

                    //cout << "(" << key << ", " << val << ")" << endl;

                    // If name is the key, this is the start of a new node. Therefore, make a new node
                    if (key == "name") {
                        if (temp != NULL) {
                            items->enqueue(temp);
                        }
                        temp = new ItemNode();
                        temp->name = val;
                    }
                    else if (key == "category") {
                        temp->category = val;
                    }
                    else if (key == "count") {
                        temp->count = stoi(val);
                    }
                    else if (key == "expiry") {
                        temp->expiry = stoi(val);
                    }
                    else if (key == "price") {
                        temp->price = stof(val);
                    }
                }

            }

        }

        return items;

    }

    Product<float>* convert(ItemNode* i) {
        Product<float>* newProd = new Product<float>();
        newProd->name = i->name;
        newProd->expiry = i->expiry;
        newProd->count = i->count;
        newProd->price = i->price;

        return newProd;
    }

    void sortData() {
        sorted = new CategoryDoubleLinkedList();

        ItemNode* nodeBeingSorted = unsortedData->dequeue();
        LinkedListNode<float>* categoryMatch = NULL;

        // Create temp node object (aka an itemnode without the category) which will be populated with the
        // data being sorted, then stored in the appropriate categoryqueue
        Product<float>* newProd;

        while (nodeBeingSorted != NULL) {
            // Generate a node to populate the sortedData
            newProd = this->convert(nodeBeingSorted);

            // Get the pointer to the CategoryNode which matches the category of the item being sorted.
            // If no match is found, this function will return NULL. That case is captured in the following if statement.
            categoryMatch = sorted->search(nodeBeingSorted->category);

            // If there is no matching category, make a new one to add to the sortedData
            if (categoryMatch == NULL) {
                categoryMatch = new LinkedListNode<float>(nodeBeingSorted->category);
                categoryMatch->insertProduct(*newProd);
                sorted->push(categoryMatch);
            }
            // If a match is found, just add the newNode to it and continue
            else {
                categoryMatch->insertProduct(*newProd);
            }

            // Dequeue the next node to be sorted here
            nodeBeingSorted = unsortedData->dequeue();
        }

        return;
    }

    void printNode(Node<float>* node) {
        cout<<"Name: "<<node->product.name<<", Expiry: "<<node->product.expiry<<", Price: "<<node->product.price<<", Count: "<<node->product.count<<endl;
    }


public:

    JSONInterface() {
        unsortedData = NULL;
    }

    void readData(string filename) {
        string allData = this->getRawData(filename);
        unsortedData = this->parseData(allData);
        this->sortData();
    }

    CategoryDoubleLinkedList* getCatalogue() {
        return sorted;
    }

    void printSortedData() {

        cout << "DISPLAYING CATALOGUE\n\n";

        LinkedListNode<float>* category = sorted->getFirst();

        while (category != NULL) {
            cout << "Category: " << category->key << endl;

            category->displayProducts();

            category = category->next;
        }

        return;
    }




};


#endif //JSONPARSING_JSONPARSER_H
