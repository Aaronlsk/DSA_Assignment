// ActorHashTable.h
#ifndef ACTORHASHTABLE_H
#define ACTORHASHTABLE_H

#include "Actor.h"
#include <vector>
#include <list>
using namespace std;

class ActorHashTable {
private:
    vector<list<Actor>> table;
    int capacity;

    int hashFunction(int key) const;

public:
    list<Actor>& getBucket(int index); // Declare the method
    ActorHashTable(int capacity);

    bool addActor(const Actor& actor);
    Actor* getActor(int id);
    bool removeActor(int id);
};

#endif // ACTORHASHTABLE_H