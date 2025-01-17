// HashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Actor.h"
#include "Movie.h"
#include <vector>
#include <list>
using namespace std;

template <typename T>
class HashTable {
private:
    vector<list<T>> table;
    int capacity;

    int hashFunction(int key) const;

public:
    HashTable(int capacity);

    bool addItem(const T& item);
    T* getItem(int id);
    bool removeItem(int id);
};

#endif // HASHTABLE_H