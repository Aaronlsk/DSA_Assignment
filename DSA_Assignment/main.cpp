#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <vector>
#include "Actor.h"
#include "Movie.h"
#include "HashTable.h"
#include <regex>

using namespace std;

void loadActors(const string& filename, HashTable<int, Actor>& actorTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;
    while (getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false; // Skip header row
            continue;
        }

        stringstream ss(line);
        string idStr, name, birthYearStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, birthYearStr, ',');

        if (idStr.empty() || name.empty() || birthYearStr.empty()) {
            cerr << "Error: Malformed row in actors.csv: " << line << endl;
            continue;
        }

        try {
            int id = stoi(idStr);
            int birthYear = stoi(birthYearStr);
            Actor actor(id, name, birthYear);
            actorTable.insert(id, actor);
        }
        catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid numeric data in actors.csv: " << line << endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            cerr << "Error: Numeric value out of range in actors.csv: " << line << endl;
            continue;
        }
    }

    cout << "Actors loaded successfully from " << filename << endl;
    file.close();
}

void loadMovies(const string& filename, HashTable<int, Movie>& movieTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false; // Skip the header row
            continue;
        }

        stringstream ss(line);
        string idStr, title, releaseYearStr;

        // Parse the movie ID
        getline(ss, idStr, ',');

        // Parse the title (quoted or unquoted)
        if (ss.peek() == '"') {
            getline(ss, title, '"'); // Skip opening quote
            getline(ss, title, '"'); // Read the quoted title
            ss.ignore(1, ',');      // Skip the comma after the closing quote
        }
        else {
            getline(ss, title, ','); // Read unquoted title
        }

        // Skip description (up to the last comma before the release year)
        string temp;
        while (getline(ss, temp, ',')) {
            if (regex_match(temp, regex("\\d+"))) { // Look for a numeric year
                releaseYearStr = temp;
                break;
            }
        }

        // Validate fields
        if (idStr.empty() || title.empty() || releaseYearStr.empty()) {
            cerr << "Error: Malformed row in movies.csv: " << line << endl;
            continue; // Skip malformed rows
        }

        try {
            int id = stoi(idStr);
            int releaseYear = stoi(releaseYearStr);
            Movie movie(id, title, releaseYear);
            movieTable.insert(id, movie);
        }
        catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid numeric data in movies.csv: " << line << endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            cerr << "Error: Numeric value out of range in movies.csv: " << line << endl;
            continue;
        }
    }

    cout << "Movies loaded successfully from " << filename << endl;
    file.close();
}



void loadCast(const string& filename, HashTable<int, vector<int>>& actorToMovies, HashTable<int, vector<int>>& movieToActors) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;
    while (getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false; // Skip header row
            continue;
        }

        stringstream ss(line);
        string actorIdStr, movieIdStr;

        getline(ss, actorIdStr, ',');
        getline(ss, movieIdStr, ',');

        if (actorIdStr.empty() || movieIdStr.empty()) {
            cerr << "Error: Malformed row in cast.csv: " << line << endl;
            continue;
        }

        try {
            int actorId = stoi(actorIdStr);
            int movieId = stoi(movieIdStr);

            // Update actor-to-movie mapping
            vector<int>* movies = actorToMovies.get(actorId);
            if (movies) {
                movies->push_back(movieId);
            }
            else {
                actorToMovies.insert(actorId, { movieId });
            }

            // Update movie-to-actor mapping
            vector<int>* actors = movieToActors.get(movieId);
            if (actors) {
                actors->push_back(actorId);
            }
            else {
                movieToActors.insert(movieId, { actorId });
            }
        }
        catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid numeric data in cast.csv: " << line << endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            cerr << "Error: Numeric value out of range in cast.csv: " << line << endl;
            continue;
        }
    }

    cout << "Cast data loaded successfully from " << filename << endl;
    file.close();
}


// Display Admin Menu
void displayAdminMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. Add New Actor\n";
    cout << "2. Add New Movie\n";
    cout << "3. Add Actor to a movie\n";
    cout << "4. Update Actor/Movie Details\n";
    cout << "5. Display All Data (Debugging)\n";
    cout << "6. Exit\n";
}

// Display User Menu
void displayUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Display Actors by Age Range\n";
    cout << "2. Display Movies from Past 3 Years\n";
    cout << "3. Display Movies by Actor\n";
    cout << "4. Display Actors in a Movie\n";
    cout << "5. Display Known Actors\n";
    cout << "6. Exit\n";
}

// Display all actors in the hash table
void displayAllActors(HashTable<int, Actor>& actorTable) {
    cout << "\nActors:\n";
    for (const auto& entry : actorTable.getAll()) {
        const Actor& actor = entry.second;
        cout << "ID: " << actor.getId()
            << ", Name: " << actor.getName()
            << ", Birth Year: " << actor.getBirthYear() << "\n";
    }
}

// Display all movies in the hash table
void displayAllMovies(HashTable<int, Movie>& movieTable) {
    cout << "\nMovies:\n";
    for (const auto& entry : movieTable.getAll()) {
        const Movie& movie = entry.second;
        cout << "ID: " << movie.getId()
            << ", Title: " << movie.getTitle()
            << ", Release Year: " << movie.getReleaseYear() << "\n";
    }
}

// Add actor to movie
void addActorToMovie(
    int actorId, int movieId,
    HashTable<int, vector<int>>& actorToMovies,
    HashTable<int, vector<int>>& movieToActors,
    HashTable<int, Actor>& actorTable,
    HashTable<int, Movie>& movieTable) {
    // Validate actor existence
    if (actorTable.get(actorId) == nullptr) {
        cout << "Error: Actor ID " << actorId << " does not exist.\n";
        return;
    }

    // Validate movie existence
    if (movieTable.get(movieId) == nullptr) {
        cout << "Error: Movie ID " << movieId << " does not exist.\n";
        return;
    }

    // Update actorToMovies
    vector<int>* movies = actorToMovies.get(actorId);
    if (movies) {
        if (find(movies->begin(), movies->end(), movieId) == movies->end()) {
            movies->push_back(movieId);
        }
        else {
            cout << "Actor ID " << actorId << " is already in Movie ID " << movieId << ".\n";
        }
    }
    else {
        actorToMovies.insert(actorId, { movieId });
    }

    // Update movieToActors
    vector<int>* actors = movieToActors.get(movieId);
    if (actors) {
        if (find(actors->begin(), actors->end(), actorId) == actors->end()) {
            actors->push_back(actorId);
        }
        else {
            cout << "Movie ID " << movieId << " already has Actor ID " << actorId << ".\n";
        }
    }
    else {
        movieToActors.insert(movieId, { actorId });
    }

    cout << "Actor ID " << actorId << " successfully added to Movie ID " << movieId << ".\n";

    // Call debugging function to display updated relationships
    cout << "\nUpdated Actor-to-Movie Relationships:\n";
    for (const auto& entry : actorToMovies.getAll()) {
        cout << "Actor ID " << entry.first << " -> Movies: ";
        for (int movieId : entry.second) {
            cout << movieId << " ";
        }
        cout << endl;
    }
}

//update actor details
void updateActorDetails(HashTable<int, Actor>& actorTable) {
    int actorId;
    cout << "Enter Actor ID to update: ";
    cin >> actorId;

    Actor* actor = actorTable.get(actorId);
    if (actor == nullptr) {
        cout << "Error: Actor ID " << actorId << " does not exist.\n";
        return;
    }

    cout << "Current Details:\n";
    cout << "Name: " << actor->getName() << ", Birth Year: " << actor->getBirthYear() << "\n";

    int choice;
    cout << "What would you like to update?\n";
    cout << "1. Name\n";
    cout << "2. Birth Year\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string newName;
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, newName);
        actor->setName(newName);
        cout << "Actor name updated successfully.\n";
    }
    else if (choice == 2) {
        int newBirthYear;
        cout << "Enter new birth year: ";
        cin >> newBirthYear;
        actor->setBirthYear(newBirthYear);
        cout << "Actor birth year updated successfully.\n";
    }
    else {
        cout << "Invalid choice. No changes made.\n";
    }

    // Display updated actor details
    cout << "\nUpdated Actor Details:\n";
    cout << "ID: " << actor->getId() << ", Name: " << actor->getName() << ", Birth Year: " << actor->getBirthYear() << "\n";
}

//update movie details
void updateMovieDetails(HashTable<int, Movie>& movieTable) {
    int movieId;
    cout << "Enter Movie ID to update: ";
    cin >> movieId;

    Movie* movie = movieTable.get(movieId);
    if (movie == nullptr) {
        cout << "Error: Movie ID " << movieId << " does not exist.\n";
        return;
    }

    cout << "Current Details:\n";
    cout << "Title: " << movie->getTitle() << ", Release Year: " << movie->getReleaseYear() << "\n";

    int choice;
    cout << "What would you like to update?\n";
    cout << "1. Title\n";
    cout << "2. Release Year\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string newTitle;
        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, newTitle);
        movie->setTitle(newTitle);
        cout << "Movie title updated successfully.\n";
    }
    else if (choice == 2) {
        int newReleaseYear;
        cout << "Enter new release year: ";
        cin >> newReleaseYear;
        movie->setReleaseYear(newReleaseYear);
        cout << "Movie release year updated successfully.\n";
    }
    else {
        cout << "Invalid choice. No changes made.\n";
    }

    // Display updated movie details
    cout << "\nUpdated Movie Details:\n";
    cout << "ID: " << movie->getId() << ", Title: " << movie->getTitle() << ", Release Year: " << movie->getReleaseYear() << "\n";
}


int main() {
    HashTable<int, Actor> actorTable(10);
    HashTable<int, Movie> movieTable(10);
    HashTable<int, vector<int>> actorToMovies(10);
    HashTable<int, vector<int>> movieToActors(10);

    loadActors("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/actors.csv", actorTable);
    loadMovies("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/movies.csv", movieTable);
    loadCast("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/cast.csv", actorToMovies, movieToActors);


    // Debugging: Display loaded data
    cout << "\nActor-to-Movie Relationships:\n";
    for (const auto& entry : actorToMovies.getAll()) {
        cout << "Actor ID " << entry.first << " -> Movies: ";
        for (int movieId : entry.second) {
            cout << movieId << " ";
        }
        cout << endl;
    }

    // Prompt user for role
    cout << "\nAre you an Admin or User? (Enter Admin/User): ";
    string role;
    cin >> role;

    // Convert input to lowercase for case-insensitivity
    std::transform(role.begin(), role.end(), role.begin(), ::tolower);

    if (role == "admin") {
        while (true) {
            displayAdminMenu();
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int id, birthYear;
                string name;
                cout << "\nEnter Actor ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Birth Year: ";
                cin >> birthYear;

                Actor actor(id, name, birthYear);
                actorTable.insert(id, actor);
                cout << "Actor added successfully!\n";
            }
            else if (choice == 2) {
                int id, releaseYear;
                string title;
                cout << "\nEnter Movie ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Release Year: ";
                cin >> releaseYear;

                Movie movie(id, title, releaseYear);
                movieTable.insert(id, movie);
                cout << "Movie added successfully!\n";
            }
            else if (choice == 3) {
                int actorId, movieId;
                cout << "\nEnter Actor ID: ";
                cin >> actorId;
                cout << "Enter Movie ID: ";
                cin >> movieId;

                addActorToMovie(actorId, movieId, actorToMovies, movieToActors, actorTable, movieTable);
            }

            else if (choice == 4) {
                int updateChoice;
                cout << "\nWhat would you like to update?\n";
                cout << "1. Actor Details\n";
                cout << "2. Movie Details\n";
                cout << "Enter choice: ";
                cin >> updateChoice;

                if (updateChoice == 1) {
                    updateActorDetails(actorTable);
                }
                else if (updateChoice == 2) {
                    updateMovieDetails(movieTable);
                }
                else {
                    cout << "Invalid choice. Returning to Admin menu.\n";
                }
            }
            else if (choice == 5) {
                cout << "\nActors:\n";
                displayAllActors(actorTable);
                cout << "\nMovies:\n";
                displayAllMovies(movieTable);
            }
            else if (choice == 6) {
                cout << "\nExiting Admin menu...\n";
                break;
            }
            else {
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
    }
    else if (role == "user") {
        while (true) {
            displayUserMenu();
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice >= 1 && choice <= 5) {
                cout << "\nUser functionality is not yet implemented.\n";
            }
            else if (choice == 6) {
                cout << "\nExiting User menu...\n";
                break;
            }
            else {
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
    }
    else {
        cout << "\nInvalid role entered. Exiting program...\n";
    }

    return 0;
}
