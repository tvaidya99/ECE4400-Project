#include <iostream>
using namespace std;

template <class T>
class Node
{
	public:
	T data;
	Node<T>* next; 
	Node<T>* prev; 
};

template <class T>
class catList : public Node<T>
{
    public:
	void append(Node<T>** head_ref, T new_data);
	void printList(Node<T>* node);
	Node<T>* search(Node<T>** head_ref, T x);	
};

template <class T> 
void catList<T>::append(Node<T>** head_ref, T new_data) 
{ 
    Node<T>* new_node = (Node<T>*)malloc(sizeof(Node<T>));
    Node<T>* last = *head_ref; 
    new_node->data = new_data; 
    new_node->next = NULL; 

    if (*head_ref == NULL)
    { 
        new_node->prev = NULL; 
        *head_ref = new_node; 
        return; 
    } 
  

    while (last->next != NULL) 
        last = last->next; 
  
    last->next = new_node; 

    new_node->prev = last; 
  
    return; 
} 

template <class T> 
void catList<T>::printList(Node<T>* node) 
{ 
    Node<T>* last; 
    cout<<"\nTraversal in forward direction \n"; 
    while (node != NULL) 
    { 
        cout<<" "<<node->data<<" "; 
        last = node; 
        node = node->next; 
    } 
  
    cout<<"\nTraversal in reverse direction \n"; 
    while (last != NULL) 
    { 
        cout<<" "<<last->data<<" "; 
        last = last->prev; 
    } 
} 

template <class T> 
Node<T>* catList<T>::search(Node** head_ref, T x)
{
 
    Node<T>* temp = *head_ref;
 

    while (temp->data != x
           && temp->next != NULL) {
 
        temp = temp->next;
    }
 
    if (temp->data != x)
	{
		return -1;
	}

 
    return (temp);
}
  

int main ()
{
    cout << "Tanmay"	;
    return 0;
}