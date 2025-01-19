#pragma once
// BST.h
#ifndef BST_H
#define BST_H

#include "Actor.h"
#include <iostream>
using namespace std;

// Node structure for the BST
struct BSTNode {
    Actor actor;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Actor& actor) : actor(actor), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    void insert(BSTNode*& node, const Actor& actor);
    void inOrderRange(BSTNode* node, int startYear, int endYear) const;
    void destroyTree(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(const Actor& actor);
    void displayRange(int startYear, int endYear) const;
};

#endif // BST_H
