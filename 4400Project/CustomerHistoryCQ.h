//
// CustomerHistoryCQ.h
//
// Document Description:
//      Declaration for the Circular Queue (implemented with a Linked List) used to
//      handle customer History
//

#ifndef CUSTOMER_HISTORY_CUSTOMERHISTORYCQ_H
#define CUSTOMER_HISTORY_CUSTOMERHISTORYCQ_H
#include <string>
using namespace std;



// ~~~~~ CUSTOMER NODE (LINKED LIST) DECLARATION ~~~~~
struct CustomerNode {
    // Customer details
    string name;
    string email;

    // Next Node reference
    CustomerNode *next;

    // Constructor Declaration
    CustomerNode(string name, string email);

    // Print Function Declaration
    void print();
};



// ~~~~~ CUSTOMER HISTORY (CIRCULAR QUEUE) DECLARATION ~~~~~
struct CustomerHistoryCQ {
    // Front and rear node references
    CustomerNode *front, *rear;

    // Size variables
    int maxSize;
    int size;

    // Constructor Declaration
    CustomerHistoryCQ(int maxSizeLocal);

    //Enqueue and Dequeue Declaration
    void enqueue(string name, string email);
    void dequeue();

    // Print function Declaration
    void print();
};



#endif //CUSTOMER_HISTORY_CUSTOMERHISTORYCQ_H


