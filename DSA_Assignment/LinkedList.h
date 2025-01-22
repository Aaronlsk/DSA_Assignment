#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef> // for nullptr
#include <utility>

// ---------------------------------------------------------------
// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K
//
// LinkedList custom implementation for hashtable (header-only)
// ---------------------------------------------------------------

template <typename T>
class LinkedList {
private:
    // Node structure
    struct Node {
        T data;
        Node* next;
        // Node constructor
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert a new node at the front
    void insert(const T& data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Nested Iterator class
    class Iterator {
    private:
        Node* current;
    public:
        // Iterator constructor
        explicit Iterator(Node* node) : current(node) {}

        // Compare iterators
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // Non-const dereference => T& 
        T& operator*() {
            return current->data;
        }

        // Const dereference => const T&
        const T& operator*() const {
            return current->data;
        }

        // Pre-increment operator
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }
    };

    // Non-const begin/end (allows modification of elements)
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    // Const begin/end (read-only)
    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // LINKEDLIST_H
