#pragma once
#include <string>
using namespace std;

class Movie
{
private:
    int id;
    string title;
    int year;

public:
    // constructors
    Movie();
    Movie(int id, string title, int year);

    // getter methods
    int getId() const;
    string getTitle() const;
    int getYear() const;

    // setter methods
    void setId(int id);
    void setTitle(const string& title);
    void setYear(int year);
};
