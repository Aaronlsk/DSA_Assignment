// HashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Actor.h"
#include <vector>
#include <list>
using namespace std;

class HashTable {
private:
    vector<list<Actor>> table;
    int capacity;

    int hashFunction(int key) const;

public:
    HashTable(int capacity);

    bool addActor(const Actor& actor);
    Actor* getActor(int id);
    bool removeActor(int id);
};

#endif // HASHTABLE_H
