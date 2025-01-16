#include "List.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor to initialize the list
template<class T>
List<T>::List() : size(0) {}

// Destructor (not required if no dynamic memory allocation is used, but we include it for completeness)
template<class T>
List<T>::~List() {}

// Add an item to the back of the list (append)
template<class T>
bool List<T>::add(T item)
{
    if (size < MAX_SIZE) {
        items[size] = item;
        size++;
        return true;
    }
    return false;
}

// Add an item at a specific index
template<class T>
bool List<T>::add(int index, T item)
{
    if (index >= 0 && index < MAX_SIZE) {
        items[index] = item;
        return true;
    }
    return false;
}

// Method to read data from a CSV file and add actors to the list
template<class T>
bool List<T>::readFromCSV(const string& filename)
{
    ifstream file(filename);
    string line;
    int id;
    string name;
    int dateOfBirth;

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return false;
    }

    // Skip header line if necessary
    getline(file, line);

    // Read each line and add it to the list
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> id;
        ss.ignore(); // Ignore the comma
        getline(ss, name, ',');
        ss >> dateOfBirth;

        Actor actor(id, name, dateOfBirth);
        add(actor);
    }

    file.close();
    return true;
}

// Method to print the list of actors
template<class T>
void List<T>::print() const
{
    for (int i = 0; i < size; ++i) {
        cout << "ID: " << items[i].getId() << ", Name: " << items[i].getName() << ", Date of Birth: " << items[i].getDateOfBirth() << endl;
    }
}

// Explicit instantiations for the Actor class
template class List<Actor>;
