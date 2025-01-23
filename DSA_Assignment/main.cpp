
// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K

// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Actor.h"
#include "Movie.h"
#include "HashTable.h"
#include "BST.h"
#include "MovieBST.h"
#include "DynamicArray.h"

using namespace std;

// ----------------------------------------------------------------------
// Feature A, E: Load actors (CSV with 3 columns: ID, name, birthYear)
// ----------------------------------------------------------------------
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
        catch (const exception& e) {
            cerr << "Error processing row in actors.csv: " << line << endl;
        }
    }
    cout << "Actors loaded successfully from " << filename << endl;
    file.close();
}

// ----------------------------------------------------------------------
// Function to parse a CSV row into a DynamicArray of strings
// ----------------------------------------------------------------------
void parseCSVRow(const string& line, DynamicArray<std::string>& fields) {
    string field;
    bool inQuotes = false;

    for (char ch : line) {
        if (ch == '"') {
            inQuotes = !inQuotes;  // Toggle inQuotes state
        }
        else if (ch == ',' && !inQuotes) {
            fields.pushBack(field);
            field.clear();
        }
        else {
            field += ch;
        }
    }
    // Add last field after loop
    fields.pushBack(field);
}

// ----------------------------------------------------------------------
// Feature B, F: Load movies (CSV with 4 columns: ID, Title, Description, Year)
// ----------------------------------------------------------------------
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

        DynamicArray<std::string> fields;
        parseCSVRow(line, fields);

        if (fields.getSize() < 4) {
            cerr << "Error: Malformed row in movies.csv: " << line << endl;
            continue;
        }

        try {
            int id = stoi(fields[0]);
            string title = fields[1];
            // fields[2] is description, we skip it
            int releaseYear = stoi(fields[3]);

            Movie movie(id, title, releaseYear);
            movieTable.insert(id, movie);
        }
        catch (const exception& e) {
            cerr << "Error processing row in movies.csv: " << line << endl;
        }
    }

    cout << "Movies loaded successfully from " << filename << endl;
    file.close();
}

// ----------------------------------------------------------------------
// Load cast.csv (actorId, movieId) into two HashTables:
// actorToMovies and movieToActors
// ----------------------------------------------------------------------
void loadCast(const string& filename,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors) {
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

        try {
            int actorId = stoi(actorIdStr);
            int movieId = stoi(movieIdStr);

            actorToMovies.getOrInsert(actorId, DynamicArray<int>()).pushBack(movieId);
            movieToActors.getOrInsert(movieId).pushBack(actorId);
        }
        catch (const exception& e) {
            cerr << "Error processing row in cast.csv: " << line << endl;
        }
    }

    cout << "Cast data loaded successfully from " << filename << endl;
    file.close();
}


// ----------------------------------------------------------------------
// Display User Menu
// ----------------------------------------------------------------------
void displayUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Display Actors within an Age Range\n";
    cout << "2. Display Movies from Past 3 Years\n";
    cout << "3. Display all movies an actor starred in (alphabetical)\n";
    cout << "4. Display all actors in a particular movie (alphabetical)\n";
    cout << "5. Display a list of all actors that a particular actor knows\n";
    cout << "6. Exit\n";
}

// ----------------------------------------------------------------------
// Display all actors
// ----------------------------------------------------------------------
void displayAllActors(HashTable<int, Actor>& actorTable) {
    cout << "\nActors:\n";
    for (const auto& entry : actorTable.getAll()) {
        const Actor& actor = entry.second;
        cout << "ID: " << actor.getId()
            << ", Name: " << actor.getName()
            << ", Birth Year: " << actor.getBirthYear()
            << ", Rating: " << actor.getRating()
            << "\n";
    }
}

// ----------------------------------------------------------------------
// Display all movies
// ----------------------------------------------------------------------
void displayAllMovies(HashTable<int, Movie>& movieTable) {
    cout << "\nMovies:\n";
    for (const auto& entry : movieTable.getAll()) {
        const Movie& movie = entry.second;
        cout << "ID: " << movie.getId()
            << ", Title: " << movie.getTitle()
            << ", Release Year: " << movie.getReleaseYear()
            << ", Rating: " << movie.getRating()
            << "\n";
    }
}

// ----------------------------------------------------------------------
// Feature C: Add actor to movie
// ----------------------------------------------------------------------
void addActorToMovie(int actorId, int movieId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    HashTable<int, Actor>& actorTable,
    HashTable<int, Movie>& movieTable) {
    if (actorTable.get(actorId) == nullptr) {
        cout << "Error: Actor ID " << actorId << " does not exist.\n";
        return;
    }
    if (movieTable.get(movieId) == nullptr) {
        cout << "Error: Movie ID " << movieId << " does not exist.\n";
        return;
    }

    DynamicArray<int>& movies = actorToMovies.getOrInsert(actorId, DynamicArray<int>());
    if (!movies.contains(movieId)) {
        movies.pushBack(movieId);
    }
    else {
        cout << "Actor ID " << actorId << " is already in Movie ID " << movieId << ".\n";
    }

    DynamicArray<int>& actors = movieToActors.getOrInsert(movieId, DynamicArray<int>());
    if (!actors.contains(actorId)) {
        actors.pushBack(actorId);
    }
    else {
        cout << "Movie ID " << movieId << " already has Actor ID " << actorId << ".\n";
    }

    cout << "Actor ID " << actorId << " successfully added to Movie ID " << movieId << ".\n";
}

// ----------------------------------------------------------------------
// Feature D: Update movie details
// ----------------------------------------------------------------------
void updateMovieDetails(HashTable<int, Movie>& movieTable) {
    int movieId;
    cout << "Enter Movie ID to update: ";
    cin >> movieId;

    Movie* movie = movieTable.get(movieId);
    if (!movie) {
        cout << "Error: Movie ID " << movieId << " does not exist.\n";
        return;
    }

    cout << "Current Details:\n";
    cout << "Title: " << movie->getTitle()
        << ", Release Year: " << movie->getReleaseYear() << "\n";

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
    cout << "ID: " << movie->getId()
        << ", Title: " << movie->getTitle()
        << ", Release Year: " << movie->getReleaseYear() << "\n";
}

// ----------------------------------------------------------------------
// Feature D: Update actor details
// ----------------------------------------------------------------------
void updateActorDetails(HashTable<int, Actor>& actorTable) {
    int actorId;
    cout << "Enter Actor ID to update: ";
    cin >> actorId;

    Actor* actor = actorTable.get(actorId);
    if (!actor) {
        cout << "Error: Actor ID " << actorId << " does not exist.\n";
        return;
    }

    cout << "Current Details:\n";
    cout << "Name: " << actor->getName()
        << ", Birth Year: " << actor->getBirthYear() << "\n";

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
    cout << "ID: " << actor->getId()
        << ", Name: " << actor->getName()
        << ", Birth Year: " << actor->getBirthYear() << "\n";
}

// ----------------------------------------------------------------------
// Feature E: Load actors into a BST for the "display actors by age range"
// ----------------------------------------------------------------------
void loadActorsToBST(const HashTable<int, Actor>& actorTable, BST& bst) {
    for (const auto& entry : actorTable.getAll()) {
        const Actor& actor = entry.second;
        bst.insert(actor);
    }
    cout << "Actors loaded into BST successfully.\n";
}

// Feature E: Display actors within an age range
void displayActorsByAgeRange(BST& bst) {
    int startYear, endYear;
    cout << "Enter the starting birth year: ";
    cin >> startYear;
    cout << "Enter the ending birth year: ";
    cin >> endYear;

    bst.displayRange(startYear, endYear);
}

// ----------------------------------------------------------------------
// Feature F: Load movies into BST (for "movies from past 3 years")
// ----------------------------------------------------------------------
void loadMoviesToBST(const string& filename, MovieBST& movieBST) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        DynamicArray<std::string> fields;
        parseCSVRow(line, fields);

        if (fields.getSize() < 4) {
            cerr << "Error: Malformed row in movies.csv: " << line << endl;
            continue;
        }

        try {
            int id = stoi(fields[0]);
            string title = fields[1];
            int releaseYear = stoi(fields[3]);

            Movie movie(id, title, releaseYear);
            movieBST.insert(movie);
        }
        catch (const exception& e) {
            cerr << "Error parsing row: " << line << " - " << e.what() << endl;
        }
    }

    file.close();
    cout << "Movies loaded into BST from " << filename << endl;
}

void displayMoviesFromPastThreeYears(MovieBST& movieBST) {
    int currentYear = 2025;
    int startYear = currentYear - 3;
    movieBST.displayInRange(startYear, currentYear);
}

// ----------------------------------------------------------------------
// Feature G: Display all movies an actor starred in (alphabetical)
// ----------------------------------------------------------------------
void sortTitles(DynamicArray<std::string>& titles) {
    for (int i = 1; i < titles.getSize(); ++i) {
        std::string currentTitle = titles[i];
        int j = i - 1;
        while (j >= 0 && titles[j] > currentTitle) {
            titles[j + 1] = titles[j];
            j--;
        }
        titles[j + 1] = currentTitle;
    }
}

void displayMoviesByActor(int actorId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, Movie>& movieTable) {
    const DynamicArray<int>* movies = actorToMovies.get(actorId);
    if (!movies) {
        cout << "Actor ID " << actorId << " not found or has no movies.\n";
        return;
    }

    DynamicArray<std::string> movieTitles;
    for (int i = 0; i < movies->getSize(); ++i) {
        int movieId = (*movies)[i];
        Movie* moviePtr = movieTable.get(movieId);
        if (moviePtr) {
            movieTitles.pushBack(moviePtr->getTitle());
        }
    }

    sortTitles(movieTitles);

    if (movieTitles.getSize() == 0) {
        cout << "Actor ID " << actorId << " has no valid movies.\n";
        return;
    }

    cout << "Movies starred by Actor ID " << actorId << ":\n";
    for (int i = 0; i < movieTitles.getSize(); ++i) {
        cout << " - " << movieTitles[i] << "\n";
    }
}

// ----------------------------------------------------------------------
// Feature H: Display all the actors in a particular movie (alphabetical)
// ----------------------------------------------------------------------
void sortNames(DynamicArray<std::string>& names) {
    for (int i = 1; i < names.getSize(); ++i) {
        std::string current = names[i];
        int j = i - 1;
        while (j >= 0 && names[j] > current) {
            names[j + 1] = names[j];
            j--;
        }
        names[j + 1] = current;
    }
}

void displayActorsByMovie(int movieId,
    HashTable<int, DynamicArray<int>>& movieToActors,
    HashTable<int, Actor>& actorTable) {
    const DynamicArray<int>* actorList = movieToActors.get(movieId);
    if (!actorList) {
        cout << "Movie ID " << movieId << " not found or has no actors.\n";
        return;
    }

    DynamicArray<std::string> actorNames;
    for (int i = 0; i < actorList->getSize(); ++i) {
        int actorId = (*actorList)[i];
        const Actor* actorPtr = actorTable.get(actorId);
        if (actorPtr) {
            actorNames.pushBack(actorPtr->getName());
        }
    }

    sortNames(actorNames);

    if (actorNames.getSize() == 0) {
        cout << "Movie ID " << movieId << " has no valid actors.\n";
        return;
    }

    cout << "Actors in Movie ID " << movieId << ":\n";
    for (int i = 0; i < actorNames.getSize(); ++i) {
        cout << " - " << actorNames[i] << "\n";
    }
}

// ----------------------------------------------------------------------
// Feature I: Display a list of all actors that a particular actor knows
// ----------------------------------------------------------------------
// DFS with depth limited to 2
void dfsKnownActors(
    int currentActorId,
    int depth,
    int maxDepth,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    DynamicArray<int>& visited,
    DynamicArray<int>& results
) {
    if (depth >= maxDepth) {
        return;
    }
    DynamicArray<int>* movies = actorToMovies.get(currentActorId);
    if (!movies) return;

    for (int i = 0; i < movies->getSize(); ++i) {
        int movieId = (*movies)[i];
        DynamicArray<int>* coActors = movieToActors.get(movieId);
        if (!coActors) continue;

        for (int j = 0; j < coActors->getSize(); ++j) {
            int coActorId = (*coActors)[j];
            bool alreadyVisited = false;
            for (int k = 0; k < visited.getSize(); ++k) {
                if (visited[k] == coActorId) {
                    alreadyVisited = true;
                    break;
                }
            }
            if (!alreadyVisited && coActorId != currentActorId) {
                visited.pushBack(coActorId);
                results.pushBack(coActorId);
                dfsKnownActors(coActorId, depth + 1, maxDepth,
                    actorToMovies, movieToActors,
                    visited, results);
            }
        }
    }
}

void getKnownActorsDFS(int startActorId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    DynamicArray<int>& results) {
    DynamicArray<int> visited;
    visited.pushBack(startActorId);
    int maxDepth = 2;
    dfsKnownActors(startActorId, 0, maxDepth,
        actorToMovies, movieToActors,
        visited, results);
}

void displayKnownActors(int startActorId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    HashTable<int, Actor>& actorTable) {
    DynamicArray<int> knownIds;
    getKnownActorsDFS(startActorId, actorToMovies, movieToActors, knownIds);

    DynamicArray<std::string> knownNames;
    for (int i = 0; i < knownIds.getSize(); ++i) {
        Actor* aPtr = actorTable.get(knownIds[i]);
        if (aPtr) {
            knownNames.pushBack(aPtr->getName());
        }
    }

    // insertion sort by name
    for (int i = 1; i < knownNames.getSize(); ++i) {
        std::string key = knownNames[i];
        int j = i - 1;
        while (j >= 0 && knownNames[j] > key) {
            knownNames[j + 1] = knownNames[j];
            j--;
        }
        knownNames[j + 1] = key;
    }

    cout << "Actors that " << startActorId << " knows (up to 2 hops):\n";
    for (int i = 0; i < knownNames.getSize(); ++i) {
        cout << " - " << knownNames[i] << "\n";
    }
}

// ----------------------------------------------------------------------
// Additional Feature 1: Capture Actor/Movie Rating (Already Implemented in Admin Menu -> Option 6)
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Additional Feature 2: Recommendations Based on Rating
//     (Show top-rated Actors, top-rated Movies)
// ----------------------------------------------------------------------
void sortActorsByRatingDesc(DynamicArray<Actor>& arr) {
    for (int i = 1; i < arr.getSize(); ++i) {
        Actor temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].getRating() < temp.getRating()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void showTopRatedActors(HashTable<int, Actor>& actorTable, int topN) {
    DynamicArray<std::pair<int, Actor>> allEntries = actorTable.getAll();
    DynamicArray<Actor> actors;

    for (int i = 0; i < allEntries.getSize(); ++i) {
        actors.pushBack(allEntries[i].second);
    }
    sortActorsByRatingDesc(actors);

    cout << "\nTop " << topN << " Actors by Rating:\n";
    for (int i = 0; i < topN && i < actors.getSize(); ++i) {
        cout << (i + 1) << ") " << actors[i].getName()
            << " (Rating: " << actors[i].getRating() << ")\n";
    }
}

void sortMoviesByRatingDesc(DynamicArray<Movie>& arr) {
    for (int i = 1; i < arr.getSize(); ++i) {
        Movie temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].getRating() < temp.getRating()) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void showTopRatedMovies(HashTable<int, Movie>& movieTable, int topN) {
    auto allEntries = movieTable.getAll();
    DynamicArray<Movie> movies;

    for (int i = 0; i < allEntries.getSize(); i++) {
        movies.pushBack(allEntries[i].second);
    }
    sortMoviesByRatingDesc(movies);

    cout << "\nTop " << topN << " Movies by Rating:\n";
    for (int i = 0; i < topN && i < movies.getSize(); ++i) {
        cout << (i + 1) << ") " << movies[i].getTitle()
            << " (Rating: " << movies[i].getRating() << ")\n";
    }
}

// ----------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------
int main() {
    HashTable<int, Actor> actorTable(10);
    HashTable<int, Movie> movieTable(10);
    HashTable<int, DynamicArray<int>> actorToMovies(10);
    HashTable<int, DynamicArray<int>> movieToActors(10);
    BST actorBST;
    MovieBST movieBST;

    // Load data
    loadActors("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/actors.csv", actorTable);
    loadMovies("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/movies.csv", movieTable);
    loadCast("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/cast.csv",
        actorToMovies, movieToActors);
    loadMoviesToBST("C:/Users/Admin/source/repos/Aaronlsk/DSA_Assignment/DSA_Assignment/movies.csv",
        movieBST);

    // Debug: Display actor->movie relationships
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
    std::transform(role.begin(), role.end(), role.begin(), ::tolower);

    if (role == "admin") {
        // =========== ADMIN MODE ===========
        while (true) {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add New Actor\n";
            cout << "2. Add New Movie\n";
            cout << "3. Add Actor to a movie\n";
            cout << "4. Update Actor/Movie Details\n";
            cout << "5. Display All Data (Debugging)\n";
            cout << "6. View Additional Features\n";
            cout << "7. Exit\n";

            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                // Add new actor
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
                // Add new movie
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
                // Add actor to movie
                int actorId, movieId;
                cout << "\nEnter Actor ID: ";
                cin >> actorId;
                cout << "Enter Movie ID: ";
                cin >> movieId;

                addActorToMovie(actorId, movieId,
                    actorToMovies, movieToActors,
                    actorTable, movieTable);
            }
            else if (choice == 4) {
                // Update actor or movie
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
                // Debug: display all
                displayAllActors(actorTable);
                displayAllMovies(movieTable);
            }
            else if (choice == 6) {
                // CHANGE #2: "View Additional Features" Submenu
                cout << "\nAdditional Features:\n";
                cout << "1. Set Actor/Movie Rating\n";
                cout << "2. Show Top-Rated Actors/Movies\n";
                cout << "Enter choice: ";
                int subChoice;
                cin >> subChoice;

                if (subChoice == 1) {
                    // Set rating
                    cout << "\n1. Actor\n2. Movie\nEnter choice: ";
                    int ratingChoice;
                    cin >> ratingChoice;

                    if (ratingChoice == 1) {
                        int actorId;
                        cout << "Enter Actor ID: ";
                        cin >> actorId;
                        Actor* actorPtr = actorTable.get(actorId);
                        if (!actorPtr) {
                            cout << "Actor with ID " << actorId << " not found.\n";
                        }
                        else {
                            double newRating;
                            cout << "Enter new rating (0.0 - 5.0): ";
                            cin >> newRating;
                            actorPtr->setRating(newRating);
                            cout << "Actor ID " << actorId << " rating updated to " << newRating << endl;
                        }
                    }
                    else if (ratingChoice == 2) {
                        int movieId;
                        cout << "Enter Movie ID: ";
                        cin >> movieId;
                        Movie* moviePtr = movieTable.get(movieId);
                        if (!moviePtr) {
                            cout << "Movie with ID " << movieId << " not found.\n";
                        }
                        else {
                            double newRating;
                            cout << "Enter new rating (0.0 - 5.0): ";
                            cin >> newRating;
                            moviePtr->setRating(newRating);
                            cout << "Movie ID " << movieId << " rating updated to " << newRating << endl;
                        }
                    }
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
                else if (subChoice == 2) {
                    // Show top-rated actors or movies
                    cout << "\n1. Show Top 5 Actors\n2. Show Top 5 Movies\nEnter choice: ";
                    int recChoice;
                    cin >> recChoice;

                    if (recChoice == 1) {
                        // Force any rating < 0 to 0.0 for display
                        showTopRatedActors(actorTable, 5);
                    }
                    else if (recChoice == 2) {
                        // Force any rating < 0 to 0.0 for display
                        showTopRatedMovies(movieTable, 5);
                    }
                    else {
                        cout << "Invalid choice.\n";
                    }
                }
                else {
                    cout << "Invalid choice.\n";
                }
            }
            else if (choice == 7) {
                cout << "\nExiting Admin menu...\n";
                break;
            }
            else {
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
    }
    else if (role == "user") {
        // =========== USER MODE ===========
        loadActorsToBST(actorTable, actorBST);

        while (true) {
            displayUserMenu();
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                // Display actors in age range
                displayActorsByAgeRange(actorBST);
            }
            else if (choice == 2) {
                // Display movies from past 3 years
                displayMoviesFromPastThreeYears(movieBST);
            }
            else if (choice == 3) {
                // Display movies for a given actor
                int actorId;
                cout << "\nEnter Actor ID: ";
                cin >> actorId;
                displayMoviesByActor(actorId, actorToMovies, movieTable);
            }
            else if (choice == 4) {
                // Display actors for a given movie
                int movieId;
                cout << "\nEnter Movie ID: ";
                cin >> movieId;
                displayActorsByMovie(movieId, movieToActors, actorTable);
            }
            else if (choice == 5) {
                // Display known actors within 2 hops
                int actorId;
                cout << "Enter Actor ID: ";
                cin >> actorId;
                displayKnownActors(actorId, actorToMovies, movieToActors, actorTable);
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
