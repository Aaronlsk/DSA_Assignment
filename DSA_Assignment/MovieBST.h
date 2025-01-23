
// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K
//Movie BST header file

#pragma once
#include "Movie.h"
#include <iostream>
using namespace std;

// Node structure for Movie BST
struct MovieNode {
    Movie movie;
    MovieNode* left;
    MovieNode* right;

    MovieNode(const Movie& movie) : movie(movie), left(nullptr), right(nullptr) {}
};

class MovieBST {
private:
    MovieNode* root;

    void insert(MovieNode*& node, const Movie& movie);
    void displayInRange(MovieNode* node, int startYear, int endYear) const;
    void destroyTree(MovieNode* node);

public:
    MovieBST();
    ~MovieBST();

    void insert(const Movie& movie);
    void displayInRange(int startYear, int endYear) const;
};
