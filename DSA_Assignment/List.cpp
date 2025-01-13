#include "List.h"  // header file
#include <fstream>
#include <sstream>
#include <string>

// constructor
List::List() { size = 0; }

// add an item to the back of the list (append)
bool List::add(ItemType item)
{
    bool success = size < MAX_SIZE;
    if (success)
    {
        items[size] = item;    // add to the end of the list
        size++;                // increase the size by 1
    }
    return success;
}

// add an item at a specified position in the list (insert)
bool List::add(int index, ItemType item)
{
    bool success = (index >= 0) && (index <= size) && (size < MAX_SIZE);
    if (success)
    {  // make room for the item by shifting all items at
       // positions >= index toward the end of the
       // List (no shift if index == size + 1)
        for (int pos = size; pos >= index; pos--)
            items[pos] = items[pos - 1];
        // insert the item
        items[index] = item;
        size++;  // increase the size by 1
    }
    return success;
}

// remove an item at a specified position in the list
void List::remove(int index)
{
    bool success = (index >= 0) && (index < size);
    if (success)
    {  // delete item by shifting all items at positions >
       // index toward the beginning of the list
       // (no shift if index == size)
        for (int pos = index; pos < size; pos++)
            items[pos] = items[pos + 1];
        size--;  // decrease the size by 1
    }
}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index)
{
    bool success = (index >= 0) && (index < size);
    if (success)
        return items[index];
    else
        return ItemType();  // return a default-constructed Actor object if index is invalid
}

// check if the list is empty
bool List::isEmpty() { return size == 0; }

// check the size of the list
int List::getLength() { return size; }

// print all items in the list
void List::print()
{
    for (int i = 0; i < size; i++)
    {
        // Assuming Actor has a method to print its details
        cout << "Actor " << i + 1 << ": "
            << items[i].getId() << ", "
            << items[i].getName() << ", "
            << items[i].getDateOfBirth() << endl;
    }
}

// replace an item in the specified index in the list
void List::replace(int index, ItemType item)
{
    bool success = (index >= 0) && (index < size);
    if (success)
    {
        items[index] = item;  // replace the item at the specified index
    }
}


// CSV Reading
bool List::readFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    // Skip header line if it exists
    getline(file, line);

    while (getline(file, line) && size < MAX_SIZE) {
        stringstream ss(line);
        int id;
        string name;
        int birthYear;
        char comma;

        if (ss >> id >> comma &&
            getline(ss, name, ',') &&
            ss >> birthYear) {

            // Create new Actor and add to list
            Actor newActor(id, name, birthYear);
            add(newActor);
        }
        else {
            cout << "Error: Invalid data format in line: " << line << endl;
        }
    }

    if (size >= MAX_SIZE) {
        cout << "Warning: List has reached max size. Some actors may not have been added." << endl;
    }

    file.close();
    return true;
}