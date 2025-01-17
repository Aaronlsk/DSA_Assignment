#pragma once
// MovieHashTable.h
#ifndef MOVIEHASHTABLE_H
#define MOVIEHASHTABLE_H

#include "Movie.h"
#include <vector>
#include <list>
using namespace std;

class MovieHashTable {
private:
    vector<list<Movie>> table;
    int capacity;

    int hashFunction(int key) const;

public:
    list<Movie>& getBucket(int index); // Declare the method
    MovieHashTable(int capacity);

    bool addMovie(const Movie& movie);
    Movie* getMovie(int id);
    bool removeMovie(int id);
};

#endif // MOVIEHASHTABLE_H