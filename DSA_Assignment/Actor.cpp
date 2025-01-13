#include "Actor.h"

// default constructor
Actor::Actor() : id(0), name(""), dateOfBirth(0) {}

// parameterized constructor
Actor::Actor(int i, string n, int dob) : id(i), name(n), dateOfBirth(dob) {}

// getter methods
int Actor::getId() const { return id; }
string Actor::getName() const { return name; }
int Actor::getDateOfBirth() const { return dateOfBirth; }

// setter methods
void Actor::setId(int i) { id = i; }
void Actor::setName(const string& n) { name = n; }
void Actor::setDateOfBirth(int dob) { dateOfBirth = dob; }

