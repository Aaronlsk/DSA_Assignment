//group name: Blue Lock
// Ng Kai Chong S10259894
//Aaron Lua Siang Kian S10258287K
//Custom Dyanmic Array to replace vectors
//No implementation file as we are using templates (allowed for use in project - Not stated under prohibited libaries)


#pragma once
#include <cstddef>
#include <stdexcept> // For std::out_of_range

template <typename T>
class DynamicArray {
private:
    T* data;           // Pointer to the dynamic array
    int capacity;      // Maximum capacity of the array
    int size;          // Current number of elements in the array

    void resize();     // Function to resize the array when needed

public:
    // 1) Default constructor
    DynamicArray();

    // 2) Copy constructor (deep copy)
    DynamicArray(const DynamicArray<T>& other);

    // 3) Copy assignment operator (deep copy)
    DynamicArray<T>& operator=(const DynamicArray<T>& other);

    // 4) Destructor
    ~DynamicArray();

    void pushBack(const T& value);
    bool contains(const T& value) const;
    T& operator[](int index);
    const T& operator[](int index) const;

    int getSize() const;
    int getCapacity() const;

    // Range-based for-loop compatibility
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};

// --------------------------------------------------
// Implementation
// --------------------------------------------------

template <typename T>
DynamicArray<T>::DynamicArray()
    : data(nullptr), capacity(0), size(0) {
}

// Copy constructor
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : data(nullptr), capacity(other.capacity), size(other.size)
{
    // Allocate our own buffer
    data = new T[capacity];
    // Copy elements from 'other'
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Copy assignment operator
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        // Free old data
        delete[] data;

        // Copy fields
        capacity = other.capacity;
        size = other.size;

        // Allocate new array and copy
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// Destructor
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    T* newData = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::pushBack(const T& value) {
    if (size == capacity) {
        resize();
    }
    data[size++] = value;
}

template <typename T>
bool DynamicArray<T>::contains(const T& value) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
int DynamicArray<T>::getCapacity() const {
    return capacity;
}

template <typename T>
T* DynamicArray<T>::begin() {
    return data;
}

template <typename T>
T* DynamicArray<T>::end() {
    return data + size;
}

template <typename T>
const T* DynamicArray<T>::begin() const {
    return data;
}

template <typename T>
const T* DynamicArray<T>::end() const {
    return data + size;
}
