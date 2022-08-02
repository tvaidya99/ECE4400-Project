#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "CustomerHistoryCQMethod.h"
#include "DoubleLinkedList.h"
#include "jsonParser.h"

using namespace std;
CustomerHistoryCQ quo;


// template <typename PriceDataType>
// LinkedList<PriceDataType> insertProduceProducts(string key)
// {
//     LinkedList<PriceDataType> products(key);
//     Product<PriceDataType> product;

//     product.name = "Spinach";
//     product.expiry = 20220731;
//     product.price = 4.99;
//     product.count = 31;
//     products.insertProduct(product);

//     product.name = "Strawberries";
//     product.price = 6.99;
//     product.expiry = 20220830;
//     product.count = 52;
//     products.insertProduct(product);

//     product.name = "Mustard greens";
//     product.price = 2.99;
//     product.expiry = 20220723;
//     product.count = 33;
//     products.insertProduct(product);

//     product.name = "Nectarines";
//     product.price = 3.99;
//     product.expiry = 20220703;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Apples";
//     product.price = 11.99;
//     product.expiry = 20220711;
//     product.count = 23;
//     products.insertProduct(product);

//     product.name = "Grapes";
//     product.price = 7.99;
//     product.expiry = 20220721;
//     product.count = 44;
//     products.insertProduct(product);

//     product.name = "Cherries";
//     product.expiry = 20220701;
//     product.price = 14.99;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Kale";
//     product.count = 65;
//     product.price = 1.99;
//     product.expiry = 20220818;
//     products.insertProduct(product);

//     return products;
// }

// template <typename PriceDataType>
// LinkedList<PriceDataType> insertDairyProducts(string key)
// {
//     LinkedList<PriceDataType> products(key);
//     Product<PriceDataType> product;

//     product.name = "Milk";
//     product.expiry = 20220731;
//     product.price = 4.99;
//     product.count = 31;
//     products.insertProduct(product);

//     product.name = "Eggs";
//     product.price = 6.99;
//     product.expiry = 20220830;
//     product.count = 52;
//     products.insertProduct(product);

//     product.name = "Yogurt";
//     product.price = 2.99;
//     product.expiry = 20220723;
//     product.count = 33;
//     products.insertProduct(product);

//     product.name = "Cheese";
//     product.price = 3.99;
//     product.expiry = 20220703;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "String Cheese";
//     product.price = 11.99;
//     product.expiry = 20220711;
//     product.count = 23;
//     products.insertProduct(product);

//     product.name = "Ice Cream";
//     product.price = 7.99;
//     product.expiry = 20220721;
//     product.count = 44;
//     products.insertProduct(product);

//     product.name = "Milk Powder";
//     product.expiry = 20220701;
//     product.price = 14.99;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Sour Cream";
//     product.count = 65;
//     product.price = 1.99;
//     product.expiry = 20220818;
//     products.insertProduct(product);

//     return products;
// }

// template <typename PriceDataType>
// LinkedList<PriceDataType> insertBakedProducts(string key)
// {
//     LinkedList<PriceDataType> products(key);
//     Product<PriceDataType> product;

//     product.name = "Bread";
//     product.expiry = 20220731;
//     product.price = 4.99;
//     product.count = 31;
//     products.insertProduct(product);

//     product.name = "Cakes";
//     product.price = 6.99;
//     product.expiry = 20220830;
//     product.count = 52;
//     products.insertProduct(product);

//     product.name = "Candy";
//     product.price = 2.99;
//     product.expiry = 20220723;
//     product.count = 33;
//     products.insertProduct(product);

//     product.name = "Confections";
//     product.price = 3.99;
//     product.expiry = 20220703;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Cookies";
//     product.price = 11.99;
//     product.expiry = 20220711;
//     product.count = 23;
//     products.insertProduct(product);

//     product.name = "Icings";
//     product.price = 7.99;
//     product.expiry = 20220721;
//     product.count = 44;
//     products.insertProduct(product);

//     product.name = "Frosting";
//     product.expiry = 20220701;
//     product.price = 14.99;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Cupcakes";
//     product.count = 65;
//     product.price = 1.99;
//     product.expiry = 20220818;
//     products.insertProduct(product);

//     return products;
// }

// template <typename PriceDataType>
// LinkedList<PriceDataType> insertInternationalProducts(string key)
// {
//     LinkedList<PriceDataType> products(key);
//     Product<PriceDataType> product;

//     product.name = "Dumplings";
//     product.expiry = 20220731;
//     product.price = 4.99;
//     product.count = 31;
//     products.insertProduct(product);

//     product.name = "Pho";
//     product.price = 6.99;
//     product.expiry = 20220830;
//     product.count = 52;
//     products.insertProduct(product);

//     product.name = "Tagine";
//     product.price = 2.99;
//     product.expiry = 20220723;
//     product.count = 33;
//     products.insertProduct(product);

//     product.name = "Dim Sum";
//     product.price = 3.99;
//     product.expiry = 20220703;
//     product.count = 39;
//     products.insertProduct(product);

//     product.name = "Gallo Pinto";
//     product.price = 11.99;
//     product.expiry = 20220711;
//     product.count = 23;
//     products.insertProduct(product);

//     product.name = "Goulash";
//     product.price = 7.99;
//     product.expiry = 20220721;
//     product.count = 44;
//     products.insertProduct(product);

//     product.name = "Jägerbraten";
//     product.expiry = 20220701;
//     product.price = 14.99;
//     product.count = 39;
//     products.insertProduct(product);

//     return products;
// }

template <typename PriceDataType>
void expirySort(int catNo)
{
    JSONInterface* json = new JSONInterface();
    json->readData("catalogue.json");
    CategoryDoubleLinkedList* catalogue = json->getCatalogue();
    LinkedList<float>* catalogueSingleCategory = json->getWholeCatalogue();
    LinkedListNode<float>* category = catalogue->getFirst();

    LinkedListNode<float>* prev = NULL;
    LinkedListNode<float>* newFirst = NULL;


    while (category != NULL) 
    {
        category = category->nodeSortTo("price");
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

    catalogue->displaybyCatProducts(catNo);

}

template <typename PriceDataType>
void displayAllCategories(string key)
{

    JSONInterface* json = new JSONInterface();
    json->readData("catalogue.json");
    CategoryDoubleLinkedList* catalogue = json->getCatalogue();
    LinkedList<float>* catalogueSingleCategory = json->getWholeCatalogue();
    LinkedListNode<float>* category = catalogue->getFirst();

    LinkedListNode<float>* prev = NULL;
    LinkedListNode<float>* newFirst = NULL;
    // int numberOfCategories = 4;

    // string *categories = new string[4];
    // categories[0] = "Produce";
    // categories[1] = "Dairy";
    // categories[2] = "Baked Goods";
    // categories[3] = "International";

    // for (int i = 0; i < numberOfCategories; i++)
    // {
    //     cout << "Press "<< i+1 << " to go to " << categories[i] << " section" << endl;
    // }

    // int x;
    // cin >> x;
    // switch (x)
    // {
    //     case 1:
    //         if(key == "price"){
    //             LinkedList<PriceDataType> producePrice = insertProduceProducts<PriceDataType>(key);
    //             displayAllProducts(producePrice, "customer");
    //         } else {
    //             LinkedList<PriceDataType> produceExpiry = insertProduceProducts<PriceDataType>(key);
    //             displayAllProducts(produceExpiry, "admin");
    //         }
    //         break;
    //     case 2:
    //         if(key == "price"){
    //             LinkedList<PriceDataType> dairyPrice = insertDairyProducts<PriceDataType>(key);
    //             displayAllProducts(dairyPrice, "customer");
    //         } else {
    //             LinkedList<PriceDataType> dairyExpiry = insertDairyProducts<PriceDataType>(key);
    //             displayAllProducts(dairyExpiry, "admin");
    //         }
    //         break;
    //     case 3:
    //         if(key == "price"){
    //             LinkedList<PriceDataType> bakedPrice = insertBakedProducts<PriceDataType>(key);
    //             displayAllProducts(bakedPrice, "customer");
    //         } else {
    //             LinkedList<PriceDataType> bakedExpiry = insertBakedProducts<PriceDataType>(key);
    //             displayAllProducts(bakedExpiry, "admin");
    //         }
    //         break;
    //     case 4:
    //         if(key == "price"){
    //             LinkedList<PriceDataType> internationalPrice = insertInternationalProducts<PriceDataType>(key);
    //             displayAllProducts(internationalPrice, "customer");
    //         } else {
    //             LinkedList<PriceDataType> internationalExpiry = insertInternationalProducts<PriceDataType>(key);
    //             displayAllProducts(internationalExpiry, "admin");
    //         }
    //         break;

    // default:
    //     break;
    // }
    int catNo;
    cout << "Please Press 1 for Dairy...."<<endl;
    cout << "Please Press 2 for Meat...."<<endl;
    cout << "Please Press 3 for Produce...."<<endl;
    cin >> catNo;
    switch (catNo)
    {
    case (1):
        if (key =="price")
        {
            cout << "Display Settings: By Category Dairy, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo);
        }
        else
        {
            expirySort(catNo);
        }
        break;
    case (2):
        if (key =="price")
        {
            cout << "Display Settings: By Category Meat, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo, key);
        }
        else
        {
            expirySort(catNo);
        }
        break;
    case (3):
        if (key =="price")
        {
            cout << "Display Settings: By Category Produce, Ordered by " << key << ".\n";
            catalogue->displaybyCatProducts(catNo);
        }
        else
        {
            expirySort(catNo);
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
    if (quo.front == NULL){
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
        if(x == 0){
            addCustomer<PriceDataType>();
        } else {
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

        if(choice == 0){
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
        LinkedList<PriceDataType> productsPrice = insertProduceProducts<PriceDataType>("price");
        displayAllCategories<PriceDataType>("price");
        //displayAllProducts<PriceDataType>(productsPrice, "customer");
    }
    // admin
    // Features include: 1. Insert/Delete item 2. Sort by expiry/price
    else if (x == 1)
    {
        LinkedList<PriceDataType> productsExpiry = insertProduceProducts<PriceDataType>("expiry");
        displayAllCategories<PriceDataType>("expiry");
        //displayAllProducts<PriceDataType>(productsExpiry, "admin");
    }
    return;
}

int main()
{
    // to test admin customer history
    quo.enqueue("Anuj", "arsevak@mun.ca");
    welcome<float>();
    return 0;
}
