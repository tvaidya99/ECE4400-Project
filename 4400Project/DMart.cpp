#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "CustomerHistoryCQMethod.h"
#include "DoubleLinkedList.h"
#include "jsonParser.h"

using namespace std;
CustomerHistoryCQ quo;
JSONInterface *json = new JSONInterface();

template <typename PriceDataType>
void expirySort(int catNo)
{
    CategoryDoubleLinkedList *catalogue = json->getCatalogue();
    LinkedList<float> *catalogueSingleCategory = json->getWholeCatalogue();
    LinkedListNode<float> *category = catalogue->getFirst();

    LinkedListNode<float> *prev = NULL;
    LinkedListNode<float> *newFirst = NULL;

    while (category != NULL)
    {
        category = category->nodeSortTo("expiry");
        // Since sortTo reassigns the pointer to a new object, the referencing needs to be updated
        if (prev != NULL)
        {
            prev->next = category;
        }
        else
        {
            newFirst = category;
        }

        // Increment along
        prev = category;
        category = category->next;
    }

    // Update the catalogue, so it is linked to the new (resorted) nodes
    catalogue->setFirstAndLast(newFirst, prev);

    if (catNo == 4)
    {
        
    }
    catalogue->displaybyCatProducts(catNo);
}

template <typename PriceDataType>
void displayAllCategories(string key)
{
    CategoryDoubleLinkedList *catalogue = json->getCatalogue();
    LinkedList<float> *catalogueSingleCategory = json->getWholeCatalogue();
    LinkedListNode<float> *category = catalogue->getFirst();

    LinkedListNode<float> *prev = NULL;
    LinkedListNode<float> *newFirst = NULL;

    int catNo;
    cout << "Please Press 1 for Dairy...." << endl;
    cout << "Please Press 2 for Meat...." << endl;
    cout << "Please Press 3 for Produce.... \n" << endl;
    cout << "Please Press 4 for All Categories... \n"<<endl;
    cin >> catNo;
    switch (catNo)
    {
    case (1):
        if (key == "price")
        {
            cout << "Display Settings: By Category Dairy, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo);
        }
        else
        {
            expirySort<PriceDataType>(catNo);
        }
        break;
    case (2):
        if (key == "price")
        {
            cout << "Display Settings: By Category Meat, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo);
        }
        else
        {
            expirySort<PriceDataType>(catNo);
        }
        break;
    case (3):
        if (key == "price")
        {
            cout << "Display Settings: By Category Produce, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo);
        }
        else
        {
            expirySort<PriceDataType>(catNo);
        }
        break;
    case(3)
        {
            if (key == "price")
            {
                cout << "Display Settings: All Category, Ordered by " << key << ".\n";
                catalogue->displaybyCatProducts(catNo);
            }
            else
            {
                expirySort<PriceDataType>(catNo);
            }
        }
        break;
    default:
        break;
    }
}

template <typename PriceDataType>
void addCustomer()
{
    cout << "Enter your name: " << endl;
    string name;
    getline(cin >> ws, name);
    string email;
    cout << "Enter your email: " << endl;
    getline(cin >> ws, email);
    quo.enqueue(name, email);
    displayAllCategories<PriceDataType>("price");
}

template <typename PriceDataType>
void printCustomers()
{
    if (quo.front == NULL)
    {
        cout << "No customers yet." << endl;
        displayAllCategories<PriceDataType>("expiry");
    }
    quo.print();
    displayAllCategories<PriceDataType>("expiry");
}

template <typename PriceDataType>
void displayAllProducts(LinkedList<PriceDataType> products, string user)
{
    products.displayProducts();
    if (user == "customer")
    {
        cout << "Press 0 to sign up to receive promotional offers." << endl;
        cout << "Press 1 to go back" << endl;
        int x;
        cin >> x;
        if (x == 0)
        {
            addCustomer<PriceDataType>();
        }
        else
        {
            displayAllCategories<PriceDataType>("price");
        }
    }
    else
    {
        cout << "Press 0 to see customer history." << endl;
        cout << "Press 1 to insert an item."
             << "\n";
        cout << "Press 2 to delete an item."
             << "\n";
        if (products.key == "expiry")
        {
            cout << "Press 3 to sort by price."
                 << "\n";
        }
        else
        {
            cout << "Press 3 to sort by expiry."
                 << "\n";
        }

        int choice;
        cin >> choice;

        if (choice == 0)
        {
            printCustomers<PriceDataType>();
        }
        // insert product
        else if (choice == 1)
        {
            Product<PriceDataType> product;
            cout << "\nEnter name of the product: ";
            getline(cin >> ws, product.name);
            cout << "\nEnter count of the product: ";
            cin >> product.count;
            cout << "\nEnter price of the product: ";
            cin >> product.price;
            cout << "\nEnter expiry of the product: ";
            cin >> product.expiry;
            products.insertProduct(product);
            displayAllProducts<PriceDataType>(products, user);
        }
        // delete product
        else if (choice == 2)
        {
            string name;
            cout << "\nEnter name of the product: ";
            getline(cin >> ws, name);
            products.deleteProduct(name);
            displayAllProducts<PriceDataType>(products, user);
        }
        else
        {
            string sortBy = "price";
            if (products.key == "price")
            {
                sortBy = "expiry";
            }

            LinkedList<PriceDataType> sortedList = products.sortTo(sortBy);
            displayAllProducts<PriceDataType>(sortedList, user);
        }
    }
}

template <typename PriceDataType>
void welcome()
{
    cout << "Welcome to the Store! \n";
    cout << "Press 2 to sign in as a customer \n";
    cout << "Press 1 to sign in as an admin \n";
    cout << "Press 0 to exit the store \n";
    int x = 1;
    cin >> x;

    // customer
    // Features include: 1. Show products 2. Sort by price
    if (x == 2)
    {
        //LinkedList<PriceDataType> productsPrice = insertProduceProducts<PriceDataType>("price");
        displayAllCategories<PriceDataType>("price");
        //displayAllProducts<PriceDataType>(productsPrice, "customer");
    }
    // admin
    // Features include: 1. Insert/Delete item 2. Sort by expiry/price
    else if (x == 1)
    {
        //LinkedList<PriceDataType> productsExpiry = insertProduceProducts<PriceDataType>("expiry");
        displayAllCategories<PriceDataType>("expiry");
        //displayAllProducts<PriceDataType>(productsExpiry, "admin");
    }
    return;
}

int main()
{
    // to test admin customer history
    quo.enqueue("Anuj", "arsevak@mun.ca");
    json->readData("catalogue.json");
    welcome<float>();
    return 0;
}
