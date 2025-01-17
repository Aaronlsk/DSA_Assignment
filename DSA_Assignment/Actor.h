#pragma once
#include <string>
using namespace std;

class Actor
{
private:
    int id;
    string name;
    int birthYear;

public:
    // constructors
    Actor();
    Actor(int id, string name, int birthYear);

    // getter methods
    int getId() const;
    string getName() const;
    int getBirthYear() const;

    // setter methods
    void setId(int id);
    void setName(const string& name);
    void setBirthYear(int by);
};
