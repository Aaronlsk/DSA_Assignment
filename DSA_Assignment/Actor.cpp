// Actor.cpp
#include "Actor.h"

Actor::Actor() : id(-1), name(""), birthYear(0) {} // Default constructor

Actor::Actor(int id, const string& name, int birthYear) : id(id), name(name), birthYear(birthYear) {}

int Actor::getId() const {
    return id;
}

string Actor::getName() const {
    return name;
}

int Actor::getBirthYear() const {
    return birthYear;
}

void Actor::setName(const string& name) {
    this->name = name;
}

void Actor::setBirthYear(int birthYear) {
    this->birthYear = birthYear;
}
