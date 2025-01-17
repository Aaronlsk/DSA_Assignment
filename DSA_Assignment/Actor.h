// Actor.h
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

class Actor {
private:
    int id;
    string name;
    int birthYear;

public:
    Actor(); // Default constructor
    Actor(int id, const string& name, int birthYear);

    int getId() const;
    string getName() const;
    int getBirthYear() const;

    void setName(const string& name);
    void setBirthYear(int birthYear);
};

#endif // ACTOR_H
