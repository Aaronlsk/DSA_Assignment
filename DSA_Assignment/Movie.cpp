#include "Movie.h"

Movie::Movie(int id, const string& title, int releaseYear) : id(id), title(title), releaseYear(releaseYear) {}

int Movie::getId() const {
    return id;
}

string Movie::getTitle() const {
    return title;
}

int Movie::getReleaseYear() const {
    return releaseYear;
}

void Movie::setTitle(const string& title) {
    this->title = title;
}

void Movie::setReleaseYear(int releaseYear) {
    this->releaseYear = releaseYear;
}
