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
CustomerNode::CustomerNode(string name, string email) : name(name), email(email)
{
    next = NULL;
}

// Print function Implementation
// Prints only the name and email
void CustomerNode::print()
{
    cout << name << ": " << email << endl;
    return;
}

// ~~~~~ CUSTOMER HISTORY (CIRCULAR QUEUE) IMPLEMENTATION ~~~~~

// Constructor Implementation
// Creates an empty Circular Queue object
CustomerHistoryCQ::CustomerHistoryCQ(int maxSizeLocal)
{
    maxSize = maxSizeLocal;
    front = rear = NULL;
}

// Enqueue Implementation
// Takes the arguments required for a Customer Node and adds a new node with
// those details to the queue
void CustomerHistoryCQ::enqueue(string name, string email)
{
    // Create a new Customer Node
    CustomerNode *temp = new CustomerNode(name, email);

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
void CustomerHistoryCQ::dequeue()
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
void CustomerHistoryCQ::print()
{
    // Special case: Queue is empty
    if (size < 1)
    {
        cout << "Empty Customer History.\n";
        return;
    }

    // Navigation node
    CustomerNode *temp = front;

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
