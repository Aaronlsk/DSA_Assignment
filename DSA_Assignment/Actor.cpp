#include "Actor.h"

// default constructor
Actor::Actor() : id(0), name(""), birthYear(0) {}

// parameterized constructor
Actor::Actor(int i, string n, int by) : id(i), name(n), birthYear(by) {}

// getter methods
int Actor::getId() const { return id; }
string Actor::getName() const { return name; }
int Actor::getBirthYear() const { return birthYear; }

// setter methods
void Actor::setId(int i) { id = i; }
void Actor::setName(const string& n) { name = n; }
void Actor::setBirthYear(int by) { birthYear = by; }

