#include <iostream>
#include "Cat-MainTree.h"

using namespace std;

template <typename PriceDataType>
LinkedList<PriceDataType> insertProducts(string key)
{
    LinkedList<PriceDataType> products(key);
    Product<PriceDataType> product;

    // populate products in the btree
    product.name = "Milk";
    product.expiry = 20220731;
    product.price = 4.99;
    product.count = 31;
    products.insertProduct(product);

    product.name = "Eggs";
    product.price = 6.99;
    product.expiry = 20220830;
    product.count = 52;
    products.insertProduct(product);

    product.name = "Yogurt";
    product.price = 2.99;
    product.expiry = 20220723;
    product.count = 33;
    products.insertProduct(product);

    product.name = "Cheese";
    product.price = 3.99;
    product.expiry = 20220703;
    product.count = 39;
    products.insertProduct(product);

    product.name = "String Cheese";
    product.price = 11.99;
    product.expiry = 20220711;
    product.count = 23;
    products.insertProduct(product);

    product.name = "Ice Cream";
    product.price = 7.99;
    product.expiry = 20220721;
    product.count = 44;
    products.insertProduct(product);

    product.name = "Milk Powder";
    product.expiry = 20220701;
    product.price = 14.99;
    product.count = 39;
    products.insertProduct(product);

    product.name = "Sour Cream";
    product.count = 65;
    product.price = 1.99;
    product.expiry = 20220818;
    products.insertProduct(product);

    return products;
}

template <typename PriceDataType>
void displayAllCategories(string key){
    catList<PriceDataType> catObj;
    catObj.rootNode("Meat and Dairy");
    catObj.append("International");
    catObj.append("Produce");
    catObj.append("Frozen");
    catObj.printList();
    cout << "Please press the number assosiated with category for category.." <<endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        if(key == "price"){
            Nodes<PriceDataType> *CatPrice = catObj.searchPrice(x-1);
            CatPrice->priceSorted = &(insertProducts<PriceDataType>(key);
        } else {
            LinkedList<PriceDataType> *CatExpiry = catObj.searchExpiry(x-1);
            CatExpiry = (insertProducts<PriceDataType>(key));
        }
        break;
    case 2:
        if(key == "price"){
            catObj.searchPrice(x-1)= insertProducts<PriceDataType>(key);
        } else {
            catObj.searchExpiry(x-1)= insertProducts<PriceDataType>(key);
        }
        break;
    case 3:
         if(key == "price"){
            catObj.searchPrice(x-1)= insertProducts<PriceDataType>(key);
        } else {
            catObj.searchExpiry(x-1)= insertProducts<PriceDataType>(key);
        }
        break;
    case 4:
         if(key == "price"){
            catObj.searchPrice(x-1)= insertProducts<PriceDataType>(key);
        } else {
            catObj.searchExpiry(x-1)= insertProducts<PriceDataType>(key);
        }
        break;
    
    default:
        break;
    }
    
}

template <typename PriceDataType>
void displayAllProducts(LinkedList<PriceDataType> products, string user)
{
    products.displayProducts();
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

        // provide option to go back to categories menu

        int choice;
        cin >> choice;

        // insert product
        if (choice == 1)
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
            if(products.key == "price"){
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
        LinkedList<PriceDataType> productsPrice = insertProducts<PriceDataType>("price");
        displayAllCategories<PriceDataType>("price");
        // display all products
        //displayAllProducts<PriceDataType>(productsPrice, "customer");
    }
    // admin
    // Features include: 1. Insert/Delete item 2. Sort by expiry/price
    else if (x == 1)
    {
        LinkedList<PriceDataType> productsExpiry = insertProducts<PriceDataType>("expiry");
        displayAllCategories<PriceDataType>("expiry");
        // display all products
        //displayAllProducts<PriceDataType>(productsExpiry, "admin");
    }
    return;
}

int main()
{
    welcome<float>();
    return 0;
}
