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
template <class stringType>
class CustomerNode {
    public:
    // Customer details
    stringType name;
    stringType email;

    // Next Node reference
    CustomerNode *next;

    // Constructor Declaration
    CustomerNode(stringType name, stringType email);

    // Print Function Declaration
    void print();
};



// ~~~~~ CUSTOMER HISTORY (CIRCULAR QUEUE) DECLARATION ~~~~~
template <class stringType>
class CustomerHistoryCQ {
    public:
    // Front and rear node references
    CustomerNode<stringType> *front, *rear;

    // Size variables
    int maxSize;
    int size;

    // Constructor Declaration
    CustomerHistoryCQ(int maxSizeLocal);

    //Enqueue and Dequeue Declaration
    void enqueue(stringType name, stringType email);
    void dequeue();

    // Print function Declaration
    void print();
};



#endif //CUSTOMER_HISTORY_CUSTOMERHISTORYCQ_H


