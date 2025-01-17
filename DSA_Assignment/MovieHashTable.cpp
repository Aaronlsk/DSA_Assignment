// MovieHashTable.cpp
#include "MovieHashTable.h"

MovieHashTable::MovieHashTable(int capacity) : capacity(capacity) {
    table.resize(capacity);
}

int MovieHashTable::hashFunction(int key) const {
    return key % capacity;
}

list<Movie>& MovieHashTable::getBucket(int index) {
    return table[index]; // Return the bucket at the given index
}

bool MovieHashTable::addMovie(const Movie& movie) {
    int index = hashFunction(movie.getId());
    for (const auto& m : table[index]) {
        if (m.getId() == movie.getId()) {
            return false; // Duplicate ID
        }
    }
    table[index].push_back(movie);
    return true;
}

Movie* MovieHashTable::getMovie(int id) {
    int index = hashFunction(id);
    for (auto& m : table[index]) {
        if (m.getId() == id) {
            return &m;
        }
    }
    return nullptr; // Not found
}

bool MovieHashTable::removeMovie(int id) {
    int index = hashFunction(id);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->getId() == id) {
            table[index].erase(it);
            return true;
        }
    }
    return false; // Not found
}
