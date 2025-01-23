
// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K
//Custom binary search table implementation

// BST.cpp
#include "BST.h"

// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() {
    destroyTree(root);
}

// Recursive function to delete all nodes
void BST::destroyTree(BSTNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert an actor into the BST
void BST::insert(BSTNode*& node, const Actor& actor) {
    if (!node) {
        node = new BSTNode(actor);
    }
    else if (actor.getBirthYear() < node->actor.getBirthYear()) {
        insert(node->left, actor);
    }
    else {
        insert(node->right, actor);
    }
}

void BST::insert(const Actor& actor) {
    insert(root, actor);
}

// Display actors within the specified range using in-order traversal
void BST::inOrderRange(BSTNode* node, int startYear, int endYear) const {
    if (!node) return;

    if (node->actor.getBirthYear() > startYear) {
        inOrderRange(node->left, startYear, endYear);
    }

    if (node->actor.getBirthYear() >= startYear && node->actor.getBirthYear() <= endYear) {
        cout << "Actor ID: " << node->actor.getId()
            << ", Name: " << node->actor.getName()
            << ", Birth Year: " << node->actor.getBirthYear() << endl;
    }

    if (node->actor.getBirthYear() < endYear) {
        inOrderRange(node->right, startYear, endYear);
    }
}

void BST::displayRange(int startYear, int endYear) const {
    cout << "Actors born between " << startYear << " and " << endYear << ":\n";
    inOrderRange(root, startYear, endYear);
}
