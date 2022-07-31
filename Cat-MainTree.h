#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename T1>
class Nodes
{
	public:
	string categoryName;
	int no;
	Nodes<T1>* next; 
	Nodes<T1>* prev; 
    LinkedList<T1>* priceSorted;
    LinkedList<T1>* expirySorted;
};

template <typename T1>
class catList : public Nodes<T1>
{
    public:
	int count = 0;
    Nodes<T1>* head_ref = (Nodes<T1>*)malloc(sizeof(Nodes<T1>));
	
    void rootNode(string new_data);
	void append(string new_data);
	void printList();
	Nodes<T1>* searchPrice(int catNo);	
    LinkedList<T1>* searchExpiry(int catNo);
};

template <typename T1>
void catList<T1>::rootNode(string new_data)
{
    Nodes<T1>* last = head_ref; 
    head_ref->categoryName = new_data; 
    head_ref->next = NULL; 
    head_ref->prev = NULL; 
    head_ref->no = count;
    head_ref->priceSorted = NULL;
    head_ref->expirySorted = NULL;
    count++; 
}

template <typename T1>
void catList<T1>::append(string new_data) 
{ 
    
    Nodes<T1>* new_node = (Nodes<T1>*)malloc(sizeof(Nodes<T1>));
    Nodes<T1>* last = head_ref; 
    new_node->categoryName = new_data; 
    new_node->next = NULL; 
    new_node->no = count;
    new_node->priceSorted = NULL;
    new_node->expirySorted = NULL;
    count++;
   
  
    while (last->next != NULL) 
    {
        last = last->next; 
    }

    last->next = new_node; 
    new_node->prev = last; 
} 

template <typename T1>
void catList<T1>::printList() 
{ 
    Nodes<T1>* node = head_ref;
    cout<<"\n List of Avaible Catagories \n"; 
    while (node != NULL) 
    { 
        cout<<" "<< node->no <<". "<<node->categoryName<<" " << endl; 
        node = node->next; 
    } 
} 

template <typename T1>
Nodes<T1>* catList<T1>::searchPrice(int catNo)
{
 
    Nodes<T1>* temp = head_ref;
    while (temp->no != catNo  && temp->next != NULL) 
    {
        temp = temp->next;
    }
 
    if (temp->no != catNo)
	{
		cout << "Category not found! Last Catagory returned...";
	}
    return temp;
}


template <typename T1> 
LinkedList<T1>* catList<T1>::searchExpiry(int catNo)
{
 
    Nodes<T1>* temp = head_ref;
    while (temp->no != catNo  && temp->next != NULL) 
    {
        temp = temp->next;
    }
 
    if (temp->no != catNo)
	{
		cout << "Category not found! Last Catagory returned...";
	}
    return (temp->expirySorted);
}


// int main ()
// {
//     catList<float> catObj;

//     string Tan = "Frozen";
//     catObj.append(Tan);
//     string an = "Dairy";
// 	catObj.append(an);
//     catObj.printList();
//     Nodes<float>* found;
//     cout << endl;
//     //found = catObj.search(0);
//     //cout << found->categoryName;
// 	// catObj.append(root, 'International');
// 	// catObj.append(root, 'Produce');
// 	// catObj.append(root, 'Frozen');

//     return 0;
	
// }