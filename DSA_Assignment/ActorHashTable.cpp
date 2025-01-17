// ActorHashTable.cpp
#include "ActorHashTable.h"

ActorHashTable::ActorHashTable(int capacity) : capacity(capacity) {
    table.resize(capacity);
}

int ActorHashTable::hashFunction(int key) const {
    return key % capacity;
}

bool ActorHashTable::addActor(const Actor& actor) {
    int index = hashFunction(actor.getId());
    for (const auto& a : table[index]) {
        if (a.getId() == actor.getId()) {
            return false; // Duplicate ID
        }
    }
    table[index].push_back(actor);
    return true;
}
list<Actor>& ActorHashTable::getBucket(int index) {
    return table[index]; // Return the bucket at the given index
}
Actor* ActorHashTable::getActor(int id) {
    int index = hashFunction(id);
    for (auto& a : table[index]) {
        if (a.getId() == id) {
            return &a;
        }
    }
    return nullptr; // Not found
}

bool ActorHashTable::removeActor(int id) {
    int index = hashFunction(id);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->getId() == id) {
            table[index].erase(it);
            return true;
        }
    }
    return false; // Not found
}