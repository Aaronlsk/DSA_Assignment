#include "Movie.h"

// default constructor
Movie::Movie() : id(0), title(""), year(0) {}

// parameterized constructor
Movie::Movie(int i, string t, int y) : id(i), title(t), year(y) {}

// getter methods
int Movie::getId() const { return id; }
string Movie::getTitle() const { return title; }
int Movie::getYear() const { return year; }

// setter methods
void Movie::setId(int i) { id = i; }
void Movie::setTitle(const string& t) { title = t; }
void Movie::setYear(int y) { year = y; }


