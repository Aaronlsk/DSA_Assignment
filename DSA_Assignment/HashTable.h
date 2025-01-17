#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
using namespace std;

template <typename Key, typename Value>
class HashTable {
private:
    vector<list<pair<Key, Value>>> table;
    int capacity;

    int hashFunction(Key key) const {
        return key % capacity;
    }

public:
    HashTable(int capacity) : capacity(capacity) {
        table.resize(capacity);
    }

    void insert(Key key, Value value) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Update existing
                return;
            }
        }
        table[index].emplace_back(key, value); // Insert new
    }

    Value* get(Key key) {
        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr; // Not found
    }

    vector<pair<Key, Value>> getAll() const {
        vector<pair<Key, Value>> allEntries;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                allEntries.push_back(pair);
            }
        }
        return allEntries;
    }
};

#endif // HASHTABLE_H
