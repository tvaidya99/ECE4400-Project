#include <iostream>
#include "BTree.h"
using namespace std;

template <typename T>
BTree<T> insertProducts(string key)
{
    BTree<T> btree(3, key);
    Product<T> product;

    // populate products in the btree
    product.name = "Milk";
    if (key == "price")
    {
        product.key = 4.99;
    }
    else
    {
        product.key = 20220731;
    }
    product.expiry = 20220731;
    product.price = 4.99;
    product.count = 31;
    btree.insert(product);

    product.name = "Eggs";
    if (key == "price")
    {
        product.key = 6.99;
    }
    else
    {
        product.key = 20220830;
    }
    product.price = 6.99;
    product.expiry = 20220830;
    product.count = 52;
    btree.insert(product);

    product.name = "Yogurt";
    if (key == "price")
    {
        product.key = 2.99;
    }
    else
    {
        product.key = 20220723;
    }
    product.price = 2.99;
    product.expiry = 20220723;
    product.count = 33;
    btree.insert(product);

    product.name = "Cheese";
    if (key == "price")
    {
        product.key = 3.99;
    }
    else
    {
        product.key = 20220703;
    }
    product.price = 3.99;
    product.expiry = 20220703;
    product.count = 39;
    btree.insert(product);

    product.name = "String Cheese";
    if (key == "price")
    {
        product.key = 11.99;
    }
    else
    {
        product.key = 20220711;
    }
    product.price = 11.99;
    product.expiry = 20220711;
    product.count = 23;
    btree.insert(product);

    product.name = "Ice Cream";
    if (key == "price")
    {
        product.key = 7.99;
    }
    else
    {
        product.key = 20220721;
    }
    product.price = 7.99;
    product.expiry = 20220721;
    product.count = 44;
    btree.insert(product);

    product.name = "Milk Powder";
    if (key == "price")
    {
        product.key = 14.99;
    }
    else
    {
        product.key = 20220701;
    }
    product.expiry = 20220701;
    product.price = 14.99;
    product.count = 39;
    btree.insert(product);

    product.name = "Sour Cream";
    product.count = 65;
    if (key == "price")
    {
        product.key = 1.99;
    }
    else
    {
        product.key = 20220818;
    }
    product.price = 1.99;
    product.expiry = 20220818;
    btree.insert(product);

    return btree;
}

template <typename T>
void displayAllProducts(BTree<T> btree, string user)
{
    btree.root->sortedTraverse();
    if (user == "customer")
    {
        // provide option to go back to categories menu
    }
    else
    {
        cout << "Press 1 to insert an item."
             << "\n";
        cout << "Press 2 to delete an item."
             << "\n";
        if (btree.key == "expiry")
        {
            cout << "Press 3 to sort by price."
                 << "\n";
        }
        else
        {
            cout << "Press 3 to sort by expiry."
                 << "\n";
        }

        // provide option to go back to categories menu

        int choice;
        cin >> choice;

        // insert product
        if (choice == 1)
        {
            Product<T> product;
            cout << "\nEnter name of the product: ";
            cin >> product.name;
            cout << "\nEnter count of the product: ";
            cin >> product.count;
            cout << "\nEnter price of the product: ";
            cin >> product.price;
            cout << "\nEnter expiry of the product: ";
            cin >> product.key;
            btree.insert(product);
            displayAllProducts(btree, user);
        }
        // delete product
        else if (choice == 2)
        {
            T key;
            string name;
            cout << "\nEnter name of the product: ";
            cin >> name;
            if (btree.key == "expiry")
                cout << "\nEnter expiry of the product: ";
            else
                cout << "\nEnter price of the product: ";
            cin >> key;
            btree.root->deleteProduct(key, name);
            displayAllProducts(btree, user);
        }
        else
        {
            // if(btree.key == "price"){
            //     BTree<float> btreePrice = btree.sortWithKey<float>("expiry");
            //     displayAllProducts(btreePrice);
            // }
        }
    }
}

int main()
{
    //Product<float> *productsArray = new Product<float>[10];
    while (true)
    {
        cout << "Welcome to the Store! \n";
        cout << "Press 1 to sign in as a customer \n";
        cout << "Press 0 to sign in as an admin \n";
        int x = 1;
        cin >> x;

        // customer
        // Features include: 1. Show products 2. Sort by price
        if (x == 1)
        {
            BTree<float> btreePrice = insertProducts<float>("price");
            // display all products
            displayAllProducts<float>(btreePrice, "customer");
            break;
        }
        // admin
        // Features include: 1. Insert/Delete item 2. Sort by expiry/price
        else
        {
            BTree<int> btreeExpiry = insertProducts<int>("expiry");
            // display all products
            displayAllProducts<int>(btreeExpiry, "admin");
            break;
        }
    }

    return 0;
}
