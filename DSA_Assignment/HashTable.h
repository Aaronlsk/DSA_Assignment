//group name: Blue Lock
// Ng Kai Chong S10259894
//Aaron Lua Siang Kian S10258287K

//Hash Table custom implementation

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include "DynamicArray.h"
#include <utility> // For std::pair

template <typename Key, typename Value>
class HashTable {
private:
    LinkedList<std::pair<Key, Value>>* table; // Array of linked lists
    int capacity;

    // Private helper function to compute the hash index
    int hashFunction(Key key) const;

public:
    // Constructor and Destructor
    HashTable(int capacity);
    ~HashTable();

    // Core methods for insertion and retrieval
    void insert(Key key, Value value);
    Value* get(Key key);

    // Retrieve all key-value pairs as a dynamic array
    DynamicArray<std::pair<Key, Value>> getAll() const;

    // Utility method to get a value by key or insert a default value
    Value& getOrInsert(Key key, const Value& defaultValue = Value());
};

#endif // HASHTABLE_H
