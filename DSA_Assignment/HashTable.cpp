// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K

// Hash Table custom implementation

#include "HashTable.h"
#include "Movie.h"
#include "DynamicArray.h"
#include "Actor.h"
#include <utility>  // For std::pair
#include <string>   // For std::string

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(int capacity) : capacity(capacity) {
    table = new LinkedList<std::pair<Key, Value>>[capacity];
}

// Destructor
template <typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
    delete[] table;
}

// Hash function
template <typename Key, typename Value>
int HashTable<Key, Value>::hashFunction(Key key) const {
    return key % capacity;
}

// Insert into hash table
template <typename Key, typename Value>
void HashTable<Key, Value>::insert(Key key, Value value) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;  // Modify value if key exists
            return;
        }
    }
    table[index].insert({ key, value });  // Insert new key-value pair
}

// Retrieve value by key
template <typename Key, typename Value>
Value* HashTable<Key, Value>::get(Key key) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return &pair.second;  // Return pointer to value
        }
    }
    return nullptr;  // Not found
}

// Retrieve all key-value pairs
template <typename Key, typename Value>
DynamicArray<std::pair<Key, Value>> HashTable<Key, Value>::getAll() const {
    DynamicArray<std::pair<Key, Value>> allEntries;  // Dynamic array for key-value pairs
    for (int i = 0; i < capacity; ++i) {
        for (auto& pair : table[i]) {
            allEntries.pushBack(pair);  // Add each pair to the array
        }
    }
    return allEntries;  // Return all pairs
}

// Implementation for getOrInsert
template <typename Key, typename Value>
Value& HashTable<Key, Value>::getOrInsert(Key key, const Value& defaultValue) {
    Value* existing = get(key);
    if (existing) {
        return *existing;  // Return reference to existing value
    }
    insert(key, defaultValue);  // Insert default value if key doesn't exist
    return *get(key);  // Retrieve the newly inserted value
}

// Explicit instantiation for common types (if needed)
template class HashTable<int, int>;
template class HashTable<int, std::string>;
template class HashTable<int, DynamicArray<int>>;
template class HashTable<int, Movie>;
template class HashTable<int, Actor>;