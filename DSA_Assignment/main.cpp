#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "ActorHashTable.h"
#include "MovieHashTable.h"

// Function to load actors from a CSV file
void loadActorsFromFile(const string& filename, ActorHashTable& actorTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, birthYearStr;

        // Parse the line
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, birthYearStr, ',');

        if (idStr.empty() || name.empty() || birthYearStr.empty()) continue; // Skip invalid rows

        int id = stoi(idStr);
        int birthYear = stoi(birthYearStr);

        Actor actor(id, name, birthYear);
        actorTable.addActor(actor);
    }

    cout << "Actors loaded successfully from " << filename << endl;
    file.close();
}

// Function to load movies from a CSV file
void loadMoviesFromFile(const string& filename, MovieHashTable& movieTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, releaseYearStr;

        // Parse the line
        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, releaseYearStr, ',');

        if (idStr.empty() || title.empty() || releaseYearStr.empty()) continue; // Skip invalid rows

        int id = stoi(idStr);
        int releaseYear = stoi(releaseYearStr);

        Movie movie(id, title, releaseYear);
        movieTable.addMovie(movie);
    }

    cout << "Movies loaded successfully from " << filename << endl;
    file.close();
}

// Function to load cast data from a CSV file
void loadCastFromFile(
    const string& filename,
    unordered_map<int, vector<int>>& actorToMovies,
    unordered_map<int, vector<int>>& movieToActors) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string actorIdStr, movieIdStr;

        // Parse the line
        getline(ss, actorIdStr, ',');
        getline(ss, movieIdStr, ',');

        if (actorIdStr.empty() || movieIdStr.empty()) continue; // Skip invalid rows

        int actorId = stoi(actorIdStr);
        int movieId = stoi(movieIdStr);

        actorToMovies[actorId].push_back(movieId);
        movieToActors[movieId].push_back(actorId);
    }

    cout << "Cast data loaded successfully from " << filename << endl;
    file.close();
}
void displayAdminMenu() {
    cout << "Admin Menu:\n";
    cout << "1. Add New Actor\n";
    cout << "2. Add New Movie\n";
    cout << "3. Update Actor Details\n";
    cout << "4. Update Movie Details\n";
    cout << "5. Display All Data (Debugging)\n";
    cout << "6. Exit\n";
}

void displayUserMenu() {
    cout << "User Menu:\n";
    cout << "1. Display Actors by Age Range\n";
    cout << "2. Display Movies from Past 3 Years\n";
    cout << "3. Display Movies by Actor\n";
    cout << "4. Display Actors in a Movie\n";
    cout << "5. Display Known Actors\n";
    cout << "6. Exit\n";
}

// Function to print all actors in the hash table
void displayAllActors(ActorHashTable& actorTable) {
    cout << "Actors:\n";
    for (int i = 0; i < 10; ++i) { // Loop through hash table buckets
        auto& bucket = actorTable.getBucket(i); // Get the bucket
        for (const auto& actor : bucket) {      // Loop through actors in the bucket
            cout << "ID: " << actor.getId()
                << ", Name: " << actor.getName()
                << ", Birth Year: " << actor.getBirthYear() << "\n";
        }
    }
}

// Function to print all movies in the hash table
void displayAllMovies(MovieHashTable& movieTable) {
    cout << "Movies:\n";
    for (int i = 0; i < 10; ++i) { // Loop through hash table buckets
        auto& bucket = movieTable.getBucket(i); // Get the bucket
        for (const auto& movie : bucket) {      // Loop through movies in the bucket
            cout << "ID: " << movie.getId()
                << ", Title: " << movie.getTitle()
                << ", Release Year: " << movie.getReleaseYear() << "\n";
        }
    }
}

int main() {
    ActorHashTable actorTable(10); // Actor hash table
    MovieHashTable movieTable(10); // Movie hash table
    unordered_map<int, vector<int>> actorToMovies;
    unordered_map<int, vector<int>> movieToActors;

    // Load data from CSV files
    loadActorsFromFile("actors.csv", actorTable);
    loadMoviesFromFile("movies.csv", movieTable);
    loadCastFromFile("cast.csv", actorToMovies, movieToActors);

    // Debugging output: Display loaded relationships
    cout << "Loaded Actor-to-Movie Relationships:\n";
    for (const auto& pair : actorToMovies) {
        cout << "Actor ID " << pair.first << " -> Movies: ";
        for (int movieId : pair.second) {
            cout << movieId << " ";
        }
        cout << endl;
    }

    cout << "Loaded Movie-to-Actor Relationships:\n";
    for (const auto& pair : movieToActors) {
        cout << "Movie ID " << pair.first << " -> Actors: ";
        for (int actorId : pair.second) {
            cout << actorId << " ";
        }
        cout << endl;
    }


    // Prompt user for role
    cout << "Are you an Admin or User? (Enter Admin/User): ";
    string role;
    cin >> role;

    if (role == "Admin" ) {
        while (true) {
            displayAdminMenu();
            int choice;
            cin >> choice;

            if (choice == 1) {
                int id, birthYear;
                string name;
                cout << "Enter Actor ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Birth Year: ";
                cin >> birthYear;

                Actor actor(id, name, birthYear);
                if (actorTable.addActor(actor)) {
                    cout << "Actor added successfully!\n";
                }
                else {
                    cout << "Actor with this ID already exists.\n";
                }
            }
            else if (choice == 2) {
                int id, releaseYear;
                string title;
                cout << "Enter Movie ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Release Year: ";
                cin >> releaseYear;

                Movie movie(id, title, releaseYear);
                if (movieTable.addMovie(movie)) {
                    cout << "Movie added successfully!\n";
                }
                else {
                    cout << "Movie with this ID already exists.\n";
                }
            }
            else if (choice == 3 || choice == 4) {
                cout << "Update functionality is not yet implemented.\n";
            }
            else if (choice == 5) {
                // Debugging: Display all actors and movies
                cout << "Debugging Data:\n";
                displayAllActors(actorTable);
                displayAllMovies(movieTable);
            }
            else if (choice == 6) {
                cout << "Exiting Admin menu...\n";
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    else if (role == "User") {
        while (true) {
            displayUserMenu();
            int choice;
            cin >> choice;

            if (choice >= 1 && choice <= 5) {
                cout << "User functionality is not yet implemented.\n";
            }
            else if (choice == 6) {
                cout << "Exiting User menu...\n";
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    else {
        cout << "Invalid role entered. Exiting program...\n";
    }

    return 0;
}
