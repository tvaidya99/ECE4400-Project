//
// CustomerHistoryCQ.cpp
//
// Document Description:
//      Implementation for the Circular Queue (implemented with a Linked List) used to
//      handle customer History
//

#include <iostream>
#include "CustomerHistoryCQ.h"

using namespace std;

// ~~~~~ CUSTOMER NODE (LINKED LIST) IMPLEMENTATION ~~~~~

// Constructor Implementation
// Takes a name and email, but sets the next node reference to NULL
template <class stringType>
CustomerNode<stringType>::CustomerNode(stringType name, stringType email) : name(name), email(email)
{
    next = NULL;
}

// Print function Implementation
// Prints only the name and email
template <class stringType>
void CustomerNode<stringType>::print()
{
    cout << name << ": " << email << endl;
    return;
}

// ~~~~~ CUSTOMER HISTORY (CIRCULAR QUEUE) IMPLEMENTATION ~~~~~

// Constructor Implementation
// Creates an empty Circular Queue object
template <class stringType>
CustomerHistoryCQ<stringType>::CustomerHistoryCQ(int maxSizeLocal)
{
    maxSize = maxSizeLocal;
    front = rear = NULL;
}

// Enqueue Implementation
// Takes the arguments required for a Customer Node and adds a new node with
// those details to the queue
template <class stringType>
void CustomerHistoryCQ<stringType>::enqueue(stringType name, stringType email)
{
    // Create a new Customer Node
    CustomerNode<stringType> *temp = new CustomerNode<stringType>(name, email);

    // Special case: Queue will exceed max size
    // Dequeue first node
    if (size == maxSize)
    {
        this->dequeue();
    }

    // Special case: Queue is empty
    // Set rear and front equal to new node
    if (size == 0)
    {
        temp->next = temp;
        front = rear = temp;
        size++;
        return;
    }

    // Insert new node at the rear
    rear->next = temp;
    rear = temp;
    rear->next = front;
    size++;

    return;
}

// Dequeue implementation
// Removes the first node in the queue
template <class stringType>
void CustomerHistoryCQ<stringType>::dequeue()
{
    // Special case: Queue is empty
    if (size < 1)
    {
        return;
    }

    // Special case: Queue has one element
    if (size == 1)
    {
        delete front;
        front = rear = NULL;
        size--;
        return;
    }

    // Update rear referencing
    rear->next = front->next;

    // Delete front node
    delete front;
    front = rear->next;
    size--;

    return;
}

// Print function implementation
// Prints out all elements in the queue
template <class stringType>
void CustomerHistoryCQ<stringType>::print()
{
    // Special case: Queue is empty
    if (size < 1)
    {
        cout << "Empty Customer History.\n";
        return;
    }

    // Navigation node
    CustomerNode<stringType> *temp = front;

    // Formatting for first node printed
    cout << "Customer History:\n";

    // Loop through all nodes in the queue and print them
    for (int i = 0; i < size; i++)
    {
        temp->print();
        temp = temp->next;
    }

    return;
}
