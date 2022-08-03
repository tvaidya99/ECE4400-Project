#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "CustomerHistoryCQMethod.h"
#include "DoubleLinkedList.h"
#include "jsonParser.h"

using namespace std;
CustomerHistoryCQ quo(1);
JSONInterface *json = new JSONInterface();

template <typename PriceDataType>
void sortTo(int catNo, string key)
{
    CategoryDoubleLinkedList *catalogue = json->getCatalogue();

    if (catNo == 4)
    {
        LinkedList<PriceDataType> *catalogueSingleCategory = json->getWholeCatalogue();
        catalogueSingleCategory->sortTo(key);
    }
    else
    {
        LinkedListNode<PriceDataType> *category = catalogue->getFirst();
        LinkedListNode<PriceDataType> *prev = NULL;
        LinkedListNode<PriceDataType> *newFirst = NULL;
        // sort all the categories in the catalogue
        while (category != NULL)
        {
            category = category->nodeSortTo(key);
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
}

template <typename PriceDataType>
void askCustomerInfo()
{
    int x;
    cout << "Press 1 to sign up for promotional offers \n";
    cout << "Press 0 to return \n";
    cin >> x;
    if (x == 1)
    {
        addCustomer<PriceDataType>();
    }
}

template <typename PriceDataType>
void printCustomers()
{
    if (quo.front == NULL)
    {
        cout << "No customers yet." << endl;
        return;
    }
    quo.print();
}

template <typename PriceDataType>
string askForInventoryEdit(string key, int catNo, CategoryDoubleLinkedList *catalogue)
{
    catalogue->displaybyCatProducts(catNo);
    string sortToKey = key;
    if (key == "price")
    {
        sortToKey = "expiry";
    }
    else
    {
        sortToKey = "price";
    }

    cout << "Press 0 to sort to " << sortToKey << endl;
    cout << "Press 1 to insert a product. " << endl;
    cout << "Press 2 to delete a product. " << endl;
    cout << "Press 3 to go back. " << endl;
    int input;
    cin >> input;

    string name;
    Product<PriceDataType> product;

    switch (input)
    {
    case 0:
        sortTo<PriceDataType>(catNo, sortToKey);
        key = sortToKey;
        askForInventoryEdit<PriceDataType>(key, catNo, catalogue);
        break;
    case 1:
        cout << "\nEnter name of the product: ";
        getline(cin >> ws, product.name);
        cout << "\nEnter count of the product: ";
        cin >> product.count;
        cout << "\nEnter price of the product: ";
        cin >> product.price;
        cout << "\nEnter expiry of the product: ";
        cin >> product.expiry;
        catalogue->getCategory(catNo)->insertProduct(product);
        json->getWholeCatalogue()->insertProduct(product);
        askForInventoryEdit<PriceDataType>(key, catNo, catalogue);
        break;
    case 2:
        cout << "\nEnter name of the product: ";
        getline(cin >> ws, name);
        catalogue->getCategory(catNo)->deleteProduct(name);
        json->getWholeCatalogue()->deleteProduct(name);
        askForInventoryEdit<PriceDataType>(key, catNo, catalogue);
        break;
    case 3:
        break;
    default:
        break;
    }
    return key;
}

template <typename PriceDataType>
void displayAllCategories(string user, string key)
{
    CategoryDoubleLinkedList *catalogue = json->getCatalogue();
    LinkedList<PriceDataType> *catalogueSingleCategory = json->getWholeCatalogue();
    int catNo;
    cout << "Press 1 for Dairy...." << endl;
    cout << "Press 2 for Meat...." << endl;
    cout << "Press 3 for Produce.... " << endl;
    cout << "Press 4 for All Categories... \n"
         << endl;
    cout << "Press 5 to sign out \n";
    if (user == "admin")
    {
        cout << "Press 6 to show customer history" << endl;
    }
    // printCustomers for admin
    cin >> catNo;

    if (catNo > 0 && catNo < 5)
    {
        if (user == "customer")
        {
            if (catalogue->getFirst()->key == "expiry")
            {
                sortTo<PriceDataType>(catNo, "price");
            }
            if (catNo < 4)
            {
                cout << "Display Settings: By category " << catalogue->getCategory(catNo)->name << ", ordered by " << key << ".\n";
                catalogue->displaybyCatProducts(catNo);
                askCustomerInfo<PriceDataType>();
            }
            else
            {
                cout << "Display Settings: All categories, ordered by " << key << ".\n";
                catalogueSingleCategory->displayProducts();
            }

            displayAllCategories<PriceDataType>(user, key);
        }
        else
        {
            string currentSortBy = key;
            if (catNo < 4)
            {
                currentSortBy = askForInventoryEdit<PriceDataType>(currentSortBy, catNo, catalogue);
            }
            else
            {
                cout << "Display Settings: All categories, ordered by " << key << ".\n";
                // if not already sorted, sort all products to current key
                if (catalogueSingleCategory->key != key)
                {
                    sortTo<PriceDataType>(4, key);
                }
                catalogueSingleCategory->displayProducts();
            }
            displayAllCategories<PriceDataType>(user, currentSortBy);
        }
    }
    else if (catNo == 6)
    {
        printCustomers<PriceDataType>();
        displayAllCategories<PriceDataType>(user, key);
    }
    else
    {
        return;
    }
}

template <typename PriceDataType>
void welcome()
{
    LinkedList<PriceDataType> *catalogueSingleCategoryPrice = json->getWholeCatalogue();
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
        // sort all products based on price by default for customer
        if (catalogueSingleCategoryPrice->key == "expiry")
        {
            sortTo<PriceDataType>(1, "price");
            sortTo<PriceDataType>(4, "price");
        }
        displayAllCategories<PriceDataType>("customer", "price");
        welcome<PriceDataType>();
    }
    // admin
    // Features include: 1. Insert/Delete item 2. Sort by expiry/price
    else if (x == 1)
    {
        // sort all products based on expiry by default for admin
        if (catalogueSingleCategoryPrice->key == "price")
        {
            sortTo<PriceDataType>(1, "expiry");
            sortTo<PriceDataType>(4, "expiry");
        }
        displayAllCategories<PriceDataType>("admin", "expiry");
        welcome<PriceDataType>();
    }
    return;
}

int main()
{
    // to test admin customer history
    quo.enqueue("Anuj", "arsevak@mun.ca");
    // read data from json
    json->readData("catalogue.json");
    welcome<float>();
    // save data in a new file
    json->saveData();
    return 0;
}
