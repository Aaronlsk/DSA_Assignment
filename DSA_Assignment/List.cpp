#include "List.h"
#include "Actor.h"
#include "Movie.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructor
template<class T>
List<T>::List() : size(0) {}

// Destructor
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

// Generic `readFromCSV`
template<class T>
bool List<T>::readFromCSV(const string& filename)
{
    cerr << "Error: readFromCSV not implemented for this type." << endl;
    return false;
}

// Specialization for `Actor`
template<>
bool List<Actor>::readFromCSV(const string& filename)
{
    ifstream file(filename);
    string line;
    int id, dateOfBirth;
    string name;

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return false;
    }

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> id;
        ss.ignore(); 
        getline(ss, name, ',');
        ss >> dateOfBirth;

        // Remove quotes from name if present
        if (!name.empty() && name.front() == '"' && name.back() == '"') {
            name.erase(0, 1);
            name.erase(name.size() - 1);
        }

        Actor actor(id, name, dateOfBirth);
        add(actor);
    }

    file.close();
    return true;
}

// Specialization for `Movie`
template<>
bool List<Movie>::readFromCSV(const string& filename)
{
    ifstream file(filename);
    string line;
    int id, year;
    string title;

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return false;
    }

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> id;
        ss.ignore();
        getline(ss, title, ',');
        ss >> year;

        // Remove quotes from title if present
        if (!title.empty() && title.front() == '"' && title.back() == '"') {
            title.erase(0, 1);
            title.erase(title.size() - 1);
        }

        Movie movie(id, title, year);
        add(movie);
    }

    file.close();
    return true;
}

// Print method
template<class T>
void List<T>::print() const {
    cerr << "Error: print not implemented for this type." << endl;
}

template<>
void List<Actor>::print() const {
    for (int i = 0; i < size; ++i) {
        cout << "Actor[ID: " << items[i].getId()
            << ", Name: " << items[i].getName()
            << ", Birth Year: " << items[i].getBirthYear() << "]" << endl;
    }
}

template<>
void List<Movie>::print() const {
    for (int i = 0; i < size; ++i) {
        cout << "Movie[ID: " << items[i].getId()
            << ", Title: " << items[i].getTitle()
            << ", Release Year: " << items[i].getYear() << "]" << endl;
    }
}





// Explicit instantiations for `Actor` and `Movie`
template class List<Actor>;
template class List<Movie>;
