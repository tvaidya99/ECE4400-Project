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
struct OuterCategoryQueue : public Queue<CategoryQueue<T> > {
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
    LinkedList<float>* wholeCatalogue;


    // Reads all the data and returns the raw text as a string
    string getRawData() {

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

        // Enqueue the last item
        items->enqueue(temp);

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

    ItemNode* convert(Node<float>* node, string category) {
        Product<float> prod = node->product;

        ItemNode* temp = new ItemNode();
        temp->category = category;
        temp->name = prod.name;
        temp->price = prod.price;
        temp->count = prod.count;
        temp->expiry = prod.expiry;

        return temp;
    }

    void sortData() {
        sorted = new CategoryDoubleLinkedList();

        // Instantiate wholeCatalogue
        wholeCatalogue = new LinkedList<float>("price", "Whole Catalogue");

        ItemNode* nodeBeingSorted = unsortedData->dequeue();
        LinkedListNode<float>* categoryMatch = NULL;

        // Create temp node object (aka an itemnode without the category) which will be populated with the
        // data being sorted, then stored in the appropriate categoryqueue
        Product<float>* newProd;

        while (nodeBeingSorted != NULL) {
            // Generate a node to populate the sortedData
            newProd = this->convert(nodeBeingSorted);

            // Add every item to a massive LinkedList, so there is also a category which holds everything
            wholeCatalogue->insertProduct(*newProd);

            // Get the pointer to the CategoryNode which matches the category of the item being sorted.
            // If no match is found, this function will return NULL. That case is captured in the following if statement.
            categoryMatch = sorted->search(nodeBeingSorted->category);

            // If there is no matching category, make a new one to add to the sortedData
            if (categoryMatch == NULL) {
                categoryMatch = new LinkedListNode<float>("price" ,nodeBeingSorted->category);
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

    void refreshQueue() {
        // Delete the old queue and make a new one
        delete unsortedData;
        unsortedData = new Queue<ItemNode>();

        // Setup temporary navigation variables
        LinkedListNode<float>* category = sorted->getFirst();
        string categoryName;
        Node<float>* oldNode;
        ItemNode* newNode;

        // Iterate through every category in the sorted DLL
        while (category != NULL) {

            // Special case: Category is empty
            if (category->isLinkedListEmpty()) {
                continue;
            }

            categoryName = category->name;

            // Get the head of the category and navigate through each node, converting them all to ItemNodes which are pushed to the queue
            oldNode = category->getHead();

            while (oldNode != nullptr) {
                newNode = convert(oldNode, categoryName);
                unsortedData->enqueue(newNode);
                oldNode = oldNode->next;
            }

            category = category->next;

        }

        return;

    }

    string generateJSONText() {
        string data = "[";
        bool first = true;

        // This string is used to make the price only go to 2 decimal places
        string price;

        // Navigate through all unsortedData
        ItemNode* temp = unsortedData->dequeue();
        while (temp != NULL) {
            if (!first) {
                data += ",";
            }
            else {
                first = false;
            }

            price = to_string(temp->price);
            price = price.substr(0, price.find('.') + 3);

            data += "\n\t{\"name\": \"" + temp->name + "\"";
            data += ", \"category\": \"" + temp->category + "\"";
            data += ", \"price\": " + price;
            data += ", \"expiry\": " + to_string(temp->expiry);
            data += ", \"count\": " + to_string(temp->count) + "}";

            temp = unsortedData->dequeue();
        }

        data += "\n]";
        return data;
    }

    void writeToFile(string data) {
        ofstream fileHandler;
        fileHandler.open(filename);

        if (fileHandler.is_open()) {
            fileHandler << data;
            fileHandler.close();
            return;
        }

        cout << "File couldn't be opened\n";

    }


public:
    string filename;

    JSONInterface() {
        filename = "";
        unsortedData = NULL;
        sorted = NULL;
        wholeCatalogue = NULL;
    }

    void readData(string file) {
        this->filename = file;

        string allData = this->getRawData();;
        unsortedData = this->parseData(allData);
        this->sortData();
    }

    CategoryDoubleLinkedList* getCatalogue() {
        return sorted;
    }

    LinkedList<float>* getWholeCatalogue() {
        return wholeCatalogue;
    }

    // bug where this doesn't overwrite json
    void saveData(string file = "") {

        // overwrite filename variable if a new file name is passed in
        if (file != "") {
            filename = file;
        }
        // If neither variable holds a filename, use catalogue.json as a default
        else if (filename == "") {
            cout << "No filename provided to write to. Using \"catalogue.json\"" << endl;
            filename = "catalogue.json";
        }

        // Refresh the queue to have another sorted list of ItemNodes based on the sorted catalogue
        this->refreshQueue();

        // Generate a string containing all the unsorted data in a json format
        string data = this->generateJSONText();

        // Write the data to file
        this->writeToFile(data);

        cout << "Data saved to " << this->filename << ".\n";
    }

};


#endif //JSONPARSING_JSONPARSER_H
