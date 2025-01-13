#pragma once
#include <string>
using namespace std;

class Actor
{
private:
    int id;
    string name;
    int dateOfBirth;

public:
    // constructors
    Actor();
    Actor(int id, string name, int dateOfBirth);

    // getter methods
    int getId() const;
    string getName() const;
    int getDateOfBirth() const;

    // setter methods
    void setId(int id);
    void setName(const string& name);
    void setDateOfBirth(int dob);
};
