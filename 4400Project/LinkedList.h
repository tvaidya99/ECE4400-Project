#include <iostream>
using namespace std;

template <typename PriceDataType>
class Product
{
public:
    int count, expiry;
    PriceDataType price;
    string name;
};

template <typename PriceDataType>
class Node
{
public:
    Product<PriceDataType> product;
    Node<PriceDataType> *next;
};

template <typename PriceDataType>
class LinkedList
{
protected:
    int count;
    Node<PriceDataType> *head;
    Node<PriceDataType> *tail;

public:
    string key;
    string name;
    LinkedList(string keyLocal, string name = "Unnamed")
    {
        count = 0;
        key = keyLocal;
        this->name = name;
    }

    void insertProduct(Product<PriceDataType> productLocal)
    {
        Node<PriceDataType> *newNode = new Node<PriceDataType>();
        newNode->product = productLocal;
        newNode->next = NULL;
        // insert into non-empty list
        if (!isLinkedListEmpty())
        {
            Node<PriceDataType> *tempHead = head;

            // insert sort by price
            if (key == "price")
            {
                Node<PriceDataType> *prev = NULL;
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
                Node<PriceDataType> *prev = NULL;
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

        Node<PriceDataType> *tempHead = head;
        Node<PriceDataType> *prev = NULL;
        // move to the node with product name equal "productName"
        while (tempHead != NULL && tempHead->product.name != productName)
        {
            prev = tempHead;
            tempHead = tempHead->next;
        }

        // element not found
        if (tempHead == NULL)
        {
            return;
        }

        // first element needs to be deleted
        if (prev == NULL)
        {
            head = head->next;
            delete tempHead;
            count--;
        }
        // deleting element beyond first element
        else
        {
            // deleting last element
            if (tempHead->next == NULL)
            {
                tail = prev;
            }
            prev->next = tempHead->next;
            delete tempHead;
        }
    }

    void sortTo(string sortBy)
    {
        LinkedList<PriceDataType> *sortedList = new LinkedList<PriceDataType>(sortBy);
        Node<PriceDataType> *tempHead = head;
        while (tempHead != NULL)
        {
            sortedList->insertProduct(tempHead->product);
            tempHead = tempHead->next;
        }
        // delete current list to free up memory
        deleteAllProducts();
        // set current linked list to the new one
        head = sortedList->head;
        tail = sortedList->tail;
        count = sortedList->count;
        key = sortedList->key;
    }

    void displayProducts()
    {
        if (!isLinkedListEmpty())
        {
            Node<PriceDataType> *tempHead = head;

            while (tempHead != NULL)
            {
                cout << tempHead->product.name << " - $" << tempHead->product.price
                     << " - expiry on " << tempHead->product.expiry << " - In stock " << tempHead->product.count << "\n";
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
            Node<PriceDataType> *tempHead = head;
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
            // Linked List deleted!
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
