#pragma once
#include <string>
using namespace std;

class Actor
{
private:
    string name;
    string dateOfBirth;
    int age;

public:
    // constructors
    Actor();
    Actor(string name, string dateOfBirth, int age);

    // getter methods
    string getName() const;
    string getDateOfBirth() const;
    int getAge() const;

    // setter methods
    void setName(const string& name);
    void setDateOfBirth(const string& dateOfBirth);
    void setAge(int age);
};
