#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
private:
    int id;
    string title;
    int releaseYear;

public:
    Movie() : id(-1), title(""), releaseYear(0) {}
    Movie(int id, const string& title, int releaseYear);

    int getId() const;
    string getTitle() const;
    int getReleaseYear() const;

    void setTitle(const string& title);
    void setReleaseYear(int releaseYear);
};

#endif // MOVIE_H
