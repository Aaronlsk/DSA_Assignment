#ifndef ACTOR_H
#define ACTOR_H

#include <string>
using namespace std;

class Actor {
private:
    int id;
    string name;
    int birthYear;
    double rating; 
public:
    Actor() : id(-1), name(""), birthYear(0) {}
    Actor(int id, const string& name, int birthYear);

    int getId() const;
    string getName() const;
    int getBirthYear() const;

    void setName(const string& name);
    void setBirthYear(int birthYear);

    double getRating() const { return rating; }
    void setRating(double r) { rating = r; }
};

#endif // ACTOR_H
