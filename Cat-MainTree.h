#include <iostream>
using namespace std;

template <class T>
class Node
{
	public:
	T data;
	int no;
	Node<T>* next; 
	Node<T>* prev; 
	
};

template <class T>
class catList : public Node<T>
{
    public:
	int count = 0;
    Node<T>* head_ref = (Node<T>*)malloc(sizeof(Node<T>));
	void rootNode(T new_data);
	void append(T new_data);
	void printList();
	Node<T>* search(int catNo);	
};

template<class T> 
void catList<T>::rootNode(T new_data)
{
    Node<T>* last = head_ref; 
    head_ref->data = new_data; 
    head_ref->next = NULL; 
    head_ref->prev = NULL; 
    head_ref->no = count;
    count++; 
}

template <class T> 
void catList<T>::append(T new_data) 
{ 
    
    Node<T>* new_node = (Node<T>*)malloc(sizeof(Node<T>));
    Node<T>* last = head_ref; 
    new_node->data = new_data; 
    new_node->next = NULL; 
    new_node->no = count;
    count++;
   
  
    while (last->next != NULL) 
    {
        last = last->next; 
    }

    last->next = new_node; 
    new_node->prev = last; 
} 

template <class T> 
void catList<T>::printList() 
{ 
    Node<T>* node = head_ref;
    cout<<"\n List of Avaible Catagories \n"; 
    while (node != NULL) 
    { 
        cout<<" "<<node->no<<" "<<node->data<<" "; 
        node = node->next; 
    } 
} 

template <class T> 
Node<T>* catList<T>::search(int catNo)
{
 
    Node<T>* temp = head_ref;
 

    while (temp->no != catNo  && temp->next != NULL) 
    {
        temp = temp->next;
    }
 
    if (temp->no != catNo)
	{
		cout << "Catagory not found! Last Catagory returned...";
	}
    return (temp);
}
  

// int main ()
// {
//     catList<string> catObj;
//     string Tan = "Grocery";
//     string an;
//     catObj.rootNode(Tan);
//     Tan = "Frozen";
//     catObj.append(Tan);
//     an = "Dairy";
// 	catObj.append(an);
//     catObj.printList();
//     Node<string>* found;
//     found = catObj.search(1);
//     cout << found->data;
// 	// catObj.append(root, 'International');
// 	// catObj.append(root, 'Produce');
// 	// catObj.append(root, 'Frozen');

//     return 0;
	
// }