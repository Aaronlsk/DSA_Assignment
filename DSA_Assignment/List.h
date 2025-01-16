#pragma once
#include <string>
#include "Actor.h"

const int MAX_SIZE = 100;  // Maximum size for the list

// Template class declaration
template<class T>
class List
{
private:
    T items[MAX_SIZE];  // Array to store the items
    int size;           // Current size of the list

public:
    // Constructors and destructor
    List();
    ~List();

    // Method to add an item
    bool add(T item);
    bool add(int index, T item);

    // Method to read data from a CSV file
    bool readFromCSV(const string& filename);

    // Method to print list items
    void print() const;
};
