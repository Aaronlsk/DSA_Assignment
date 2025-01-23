
// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K
//Movie class header file

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
private:
    int id;
    string title;
    int releaseYear;
    double rating;

public:
    Movie() : id(-1), title(""), releaseYear(0) {}
    Movie(int id, const string& title, int releaseYear);

    int getId() const;
    string getTitle() const;
    int getReleaseYear() const;

    void setTitle(const string& title);
    void setReleaseYear(int releaseYear);

    double getRating() const { return rating; }
    void setRating(double r) { rating = r; }
};

#endif // MOVIE_H
