#include <iostream>
#include <fstream>
#include <string>
#include "DMart.cpp"
#include "jsonParser.h"
using namespace std;




void runAddDelete(int displayMode, string sortBy) {

}




// This function runs the whole program
void runSkynet() {

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
    cout << "\n\nHello, welcome to Anuj, Malcolm and Tanmay's shop.\n";


    // Set up prompt loop
    bool running = true;
    int response;

    // First prompt
    cout << "\n\nHow would you like to see the items? Enter your answer.\n1 - Display all items\n2 - Display items sorted by category\n0 - Exit shop\n\n";
    cin >> response;


    while (running) {

        switch (response) {
            case (1): // Display altogether
                displayMode = 1;
                cout << "Display Settings: No Categories, Ordered by " << sortBy << ".\n";
                catalogueSingleCategory->displayProducts();
                break;
            case (2): // Display by category
                displayMode = 2;
                cout << "Display Settings: By Category, Ordered by " << sortBy << ".\n";
                catalogue->displayProducts();
                break;
            case (3): // Swap sort method
                if (displayMode == 1) {
                    *catalogueSingleCategory = catalogueSingleCategory->sortTo(alternateSortBy);
                    catalogueSingleCategory->displayProducts();
                    string temp = sortBy;
                    sortBy = alternateSortBy;
                    alternateSortBy = sortBy;
                }
                else if (displayMode == 2) {
                    LinkedListNode<float>* category = catalogue->getFirst();
                    LinkedListNode<float>* prev = NULL;
                    LinkedListNode<float>* newFirst = NULL;


                    while (category != NULL) {
                        category = category->nodeSortTo(alternateSortBy);
                        // Since sortTo reassigns the pointer to a new object, the referencing needs to be updated
                        if (prev != NULL) {
                            prev->next = category;
                        }
                        // Special case: this is the first LinkedListNode sorting differently.
                        // in this case the head of the catalogue DLL need to be set to this. The head is reserved
                        // the first and last node can be updated at the same time after the loop. This ensures no
                        // partial switch.
                        else {
                            newFirst = category;
                        }

                        // Increment along
                        prev = category;
                        category = category->next;
                    }

                    // Update the catalogue, so it is linked to the new (resorted) nodes
                    catalogue->setFirstAndLast(newFirst, prev);

                    catalogue->displayProducts();

                    string temp = sortBy;
                    sortBy = alternateSortBy;
                    alternateSortBy = sortBy;
                }
                break;
            case (0): // Exit program
                running = false;
                cout << "Thank you for coming.";
                break;
            default:
                cout << "Invalid entry, please try again.\n\n";
        }


        // Re-prompt
        cout << "\n\nHow would you like to see the items? Enter your answer.\n1 - Display all items\n";
        cout << "2 - Display items sorted by category\n3 - Display the same way, but ordered by " << alternateSortBy << "\n0 - Exit shop\n\n";
        cin >> response;

    }
}



int main() {


    runSkynet();


    return 0;
}
