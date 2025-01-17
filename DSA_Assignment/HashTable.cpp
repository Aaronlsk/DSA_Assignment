// HashTable.cpp
#include "HashTable.h"

HashTable::HashTable(int capacity) : capacity(capacity) {
    table.resize(capacity);
}

int HashTable::hashFunction(int key) const {
    return key % capacity;
}

bool HashTable::addActor(const Actor& actor) {
    int index = hashFunction(actor.getId());
    for (const auto& a : table[index]) {
        if (a.getId() == actor.getId()) {
            return false; // Duplicate ID
        }
    }
    table[index].push_back(actor);
    return true;
}

Actor* HashTable::getActor(int id) {
    int index = hashFunction(id);
    for (auto& a : table[index]) {
        if (a.getId() == id) {
            return &a;
        }
    }
    return nullptr; // Not found
}

bool HashTable::removeActor(int id) {
    int index = hashFunction(id);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->getId() == id) {
            table[index].erase(it);
            return true;
        }
    }
    return false; // Not found
}
