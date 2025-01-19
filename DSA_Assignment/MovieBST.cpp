#include "MovieBST.h"

// Constructor
MovieBST::MovieBST() : root(nullptr) {}

// Destructor
MovieBST::~MovieBST() {
    destroyTree(root);
}

// Helper to destroy the tree
void MovieBST::destroyTree(MovieNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Insert a movie into the BST
void MovieBST::insert(const Movie& movie) {
    insert(root, movie);
}

// Recursive helper for insertion
void MovieBST::insert(MovieNode*& node, const Movie& movie) {
    if (!node) {
        node = new MovieNode(movie);
    }
    else if (movie.getReleaseYear() < node->movie.getReleaseYear()) {
        insert(node->left, movie);
    }
    else if (movie.getReleaseYear() > node->movie.getReleaseYear()) { // Ensure unique release years
        insert(node->right, movie);
    }
    else {
        // Handle duplicate release years, if needed (e.g., update or skip insertion)
        cerr << "Duplicate release year detected for movie: " << movie.getTitle() << endl;
    }
}


// Display movies in a given range
void MovieBST::displayInRange(int startYear, int endYear) const {
    displayInRange(root, startYear, endYear);
}

// Recursive helper for display
void MovieBST::displayInRange(MovieNode* node, int startYear, int endYear) const {
    if (!node) return;

    if (node->movie.getReleaseYear() >= startYear) {
        displayInRange(node->left, startYear, endYear);
    }
    if (node->movie.getReleaseYear() >= startYear && node->movie.getReleaseYear() <= endYear) {
        cout << "ID: " << node->movie.getId() << ", Title: " << node->movie.getTitle()
            << ", Release Year: " << node->movie.getReleaseYear() << "\n";
    }
    if (node->movie.getReleaseYear() <= endYear) {
        displayInRange(node->right, startYear, endYear);
    }
}



