#pragma once
#include <iostream>
#include "Actor.h"
using namespace std;

const int MAX_SIZE = 100;
typedef Actor ItemType; 

class List
{
private:
    ItemType items[MAX_SIZE]; 
    int size;

public:

    // constructor
    List();

    // add an item to the back of the list (append)
    bool add(ItemType item);

    // add an item at a specified position in the list (insert)
    bool add(int index, ItemType item);

    // remove an item at a specified position in the list
    void remove(int index);

    // get an item at a specified position of the list (retrieve)
    ItemType get(int index);

    // check if the list is empty
    bool isEmpty();

    // check the size of the list
    int getLength();

    // print all items in the list
    void print();

    // replace an item in the specified index in the list
    void replace(int index, ItemType item);

    bool readFromCSV(const string& filename);
};
