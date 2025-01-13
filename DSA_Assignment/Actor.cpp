#include "Actor.h"

// default constructor
Actor::Actor() : name(""), dateOfBirth(""), age(0) {}

// parameterized constructor
Actor::Actor(string n, string dob, int a) : name(n), dateOfBirth(dob), age(a) {}

// getter methods
string Actor::getName() const { return name; }
string Actor::getDateOfBirth() const { return dateOfBirth; }
int Actor::getAge() const { return age; }

// setter methods
void Actor::setName(const string& n) { name = n; }
void Actor::setDateOfBirth(const string& dob) { dateOfBirth = dob; }
void Actor::setAge(int a) { age = a; }

