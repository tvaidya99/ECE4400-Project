#include <iostream>
using namespace std;

class Product
{
public:
    int count, expiry;
    float price;
    string name;
};

class Node
{
public:
    Product product;
    Node *next;
};

class LinkedList
{
private:
    int listSize;
    int count;
    Node *head;
    Node *tail;

public:
    string key;
    LinkedList(int size, string keyLocal)
    {
        listSize = size;
        count = 0;
        key = keyLocal;
    }

    void insertProduct(Product productLocal)
    {
        Node *newNode = new Node();
        newNode->product = productLocal;
        newNode->next = NULL;
        // insert into non-empty list
        if (!isLinkedListEmpty())
        {
            Node *tempHead = head;

            // insert sort by price
            if (key == "price")
            {
                Node *prev = NULL;
                // move to the node with product price greater than or equal to insert "product.price"
                while (tempHead != NULL && tempHead->product.price < productLocal.price)
                {
                    prev = tempHead;
                    tempHead = tempHead->next;
                }
                // add to last
                if (tempHead == NULL)
                {
                    prev->next = newNode;
                    tail = newNode;
                }
                // add to first
                else if (prev == NULL)
                {
                    newNode->next = tempHead;
                    head = newNode;
                }
                // add between
                else
                {
                    newNode->next = tempHead;
                    prev->next = newNode;
                }
            }
            // insert sort by expiry
            else
            {
                Node *prev = NULL;
                // move to the node with product expiry greater than or equal to insert "product.expiry"
                while (tempHead != NULL && tempHead->product.expiry < productLocal.expiry)
                {
                    prev = tempHead;
                    tempHead = tempHead->next;
                }
                // add to last
                if (tempHead == NULL)
                {
                    prev->next = newNode;
                    tail = newNode;
                }
                // add to first
                else if (prev == NULL)
                {
                    newNode->next = tempHead;
                    head = newNode;
                }
                // add between
                else
                {
                    newNode->next = tempHead;
                    prev->next = newNode;
                }
            }
            count++;
        }
        // insert into empty list
        else
        {
            head = newNode;
            tail = newNode;
            count++;
        }
    }

    void deleteProduct(string productName)
    {
        if (isLinkedListEmpty())
            return;

        Node *tempHead = head;
        Node *prev = NULL;
        // move to the node with product name equal "productName"
        while (tempHead != NULL && tempHead->product.name != productName)
        {
            prev = tempHead;
            tempHead = tempHead->next;
        }

        // element not found
        if(tempHead == NULL) {
            return;
        }

        // first element needs to be deleted
        if(prev == NULL){
            head = head->next;
            delete tempHead;
            count--;
        }
        // deleting element beyond first element
        else {
            // deleting last element
            if(tempHead->next == NULL){
                tail = prev;
            }
            prev->next = tempHead->next;
            delete tempHead;
        }
    }

    void displayProducts()
    {
        if (!isLinkedListEmpty())
        {
            Node *tempHead = head;

            while (tempHead != NULL)
            {
                cout << tempHead->product.name << " - $" << tempHead->product.price
                     << " - expiry on " << tempHead->product.expiry << "\n";
                tempHead = tempHead->next;
            }
        }
    }

    // a utility function to free up memory
    void deleteAllProducts()
    {
        // continue if the linked list is not empty
        if (!isLinkedListEmpty())
        {
            Node *tempHead = head;
            while (true)
            {
                if (head->next != NULL)
                {
                    tempHead = head->next;
                }
                else
                {
                    delete head;
                    break;
                }
                delete head;
                head = tempHead;
            }
            cout << "\n"
                 << "Linked List deleted!";
            count = 0;
        }
    }

    bool isLinkedListEmpty()
    {
        // if empty, return true
        if (count == 0)
        {
            return true;
        }
        return false;
    }
};