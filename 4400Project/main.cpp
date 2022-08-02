#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "CustomerHistoryCQMethod.h"
#include "DoubleLinkedList.h"
#include "jsonParser.h"

using namespace std;




void runAddDelete(int displayMode, string sortBy) {

}





// This function runs the whole program
void runSkynet() {
    CustomerHistoryCQ quo;

    // Get the catalogue from the JSON file
    JSONInterface* json = new JSONInterface();
    json->readData("catalogue.json");
    CategoryDoubleLinkedList* catalogue = json->getCatalogue();
    LinkedList<float>* catalogueSingleCategory = json->getWholeCatalogue();

    string sortBy = "price";
    string alternateSortBy = "expiry";

    // 1 is altogether, 2 is by category
    int displayMode = 1;

    //catalogue->displayProducts();
    //cout << "\n\n\n\n";
    //catalogueSingleCategory->displayProducts();


    // Introduce ourselves


    // Set up prompt loop
    bool running = true;
    int response;
    int catNo;
    string ans;
    int choice;


    // First prompt
    // cout << "\n\nHow would you like to see the items? Enter your answer.\n1 - Display all items\n2 - Display items sorted by category\n0 - Exit shop\n\n";
    // cin >> response;


    while (running) 
    {
        CustomerHistoryCQ quo;
        cout << "\nHi Welcome to the store!\n";
        cout << "\n Are you a customer or a admin? Press 1 for customer and 2 for Admin Press 0 to exit the store. \n \n";
        cin >> response;
        switch (response)
        {
        case (0):
            cout << "\n Thank you for shopping with us! Have a wonderful day!...\n";
            break;
        case (1):
            cout << " Would you like to sign up for our newsletter? please press yes to enter the name and press anything to skip \n ";
            cin >> ans;
            if (ans == "yes" || ans == "YES" || ans == "Yes" || ans == "y")
            {
                cout << "Enter your name: " << endl;
                string name;
                getline(cin >> ws, name);
                string email;
                cout << "Enter your email: " << endl;
                getline(cin >> ws, email);
                quo.enqueue(name, email);
                cout << " \n How would like to see the products today? \n";
                cout << " Please Press 1 to see all products by price... \n Press 2 to see the products of perticular category by price \n Press 0 to exit out \n";
                cin >> choice;

                switch (choice)
                {
                case (0):
                    running = false;
                    break;
                case (1):
                    cout << " Here is the list of all products sorted by price. \n";
                    catalogueSingleCategory->displayProducts();
                    break;
                case (2):
                    cout << "Please Press 1 for Dairy...."<<endl;
                    cout << "Please Press 2 for Meat...."<<endl;
                    cout << "Please Press 3 for Produce...."<<endl;
                    cin >> catNo;
                    switch (catNo)
                    {
                    case (1):
                        cout << "Display Settings: By Category Dairy, Ordered by " << sortBy << ".\n";
                        catalogue->displaybyCatProducts(catNo);
                        break;
                    case (2):
                        cout << "Display Settings: By Category Meat, Ordered by " << sortBy << ".\n";
                        catalogue->displaybyCatProducts(catNo);
                        break;
                    case (3):
                        cout << "Display Settings: By Category Produce, Ordered by " << sortBy << ".\n";
                        catalogue->displaybyCatProducts(catNo);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;1
    
                }

            }
            else 
            {
                cout << " \n How would like to see the products today? \n";
                cout << " Please Press 1 to see all products by price... \n Press 2 to see the products of perticular category by price \n Press 0 to exit out \n";
                cin >> choice;
                switch (choice)
                {
                case (0):
                    running = false;
                    break;
                case (1):
                    cout << " Here is the list of all products sorted by price. \n";
                    catalogueSingleCategory->displayProducts();
                    break;
                default:
                    break;
                }
            }
        default:
            break;
        }
    }

}


int main() {


    runSkynet();


    return 0;
}
