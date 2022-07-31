#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename PriceDataType>
class Category
{
public:
    string name;
    LinkedList<PriceDataType>* priceSorted;
    LinkedList<PriceDataType>* expirySorted;
};

template <typename PriceDataType>
class GenericTree{
    public:
        int categoriesCount;
        Category<PriceDataType> *categories;
        GenericTree(int size){
            categoriesCount = size;
            categories = new Category<PriceDataType>[size];
        }
};