// group name: Blue Lock
// Ng Kai Chong S10259894
// Aaron Lua Siang Kian S10258287K

// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
// #include <regex> // <-- REMOVED, not being used
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
// (Already used by loadMoviesToBST, so let's reuse it in loadMovies too.)
// ----------------------------------------------------------------------
void parseCSVRow(const string& line, DynamicArray<std::string>& fields) {
    string field;
    bool inQuotes = false;

    for (char ch : line) {
        if (ch == '"') {
            inQuotes = !inQuotes;  // Toggle inQuotes state
        }
        else if (ch == ',' && !inQuotes) {
            fields.pushBack(field);  // Add the field to the array
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

        // Use the same CSV parsing function as loadMoviesToBST
        DynamicArray<std::string> fields;
        parseCSVRow(line, fields);

        // We expect at least 4 columns: ID, Title, Description, Year
        if (fields.getSize() < 4) {
            cerr << "Error: Malformed row in movies.csv: " << line << endl;
            continue;
        }

        try {
            int id = stoi(fields[0]);
            string title = fields[1];
            // fields[2] is the big description we don't store
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
// Supporting Feature for C, G, H (cast.csv presumably has only 2 columns)
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
// Display Admin Menu
// ----------------------------------------------------------------------
void displayAdminMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. Add New Actor\n";
    cout << "2. Add New Movie\n";
    cout << "3. Add Actor to a movie\n";
    cout << "4. Update Actor/Movie Details\n";
    cout << "5. Display All Data (Debugging)\n";
    cout << "6. Exit\n";
}

// ----------------------------------------------------------------------
// Display User Menu
// ----------------------------------------------------------------------
void displayUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Display Actors within an Age Range\n";
    cout << "2. Display Movies from Past 3 Years\n";
    cout << "3. Display all movies an actor starred in\n";
    cout << "4. Display all the actors in a particular movie\n";
    cout << "5. Display a list of all actors that a particular actor knows.\n";
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
            << ", Birth Year: " << actor.getBirthYear() << "\n";
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
            << ", Release Year: " << movie.getReleaseYear() << "\n";
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
    DynamicArray<int>& movies = actorToMovies.getOrInsert(actorId, DynamicArray<int>());
    if (!movies.contains(movieId)) {
        movies.pushBack(movieId);
    }
    else {
        cout << "Actor ID " << actorId << " is already in Movie ID " << movieId << ".\n";
    }

    // Update movieToActors
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
    if (movie == nullptr) {
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
    if (actor == nullptr) {
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
// Feature E: Load actors into a BST
// ----------------------------------------------------------------------
void loadActorsToBST(const HashTable<int, Actor>& actorTable, BST& bst) {
    for (const auto& entry : actorTable.getAll()) {
        const Actor& actor = entry.second;
        bst.insert(actor);
    }
    cout << "Actors loaded into BST successfully.\n";
}

// ----------------------------------------------------------------------
// Feature E: Display actors within an age range
// ----------------------------------------------------------------------
void displayActorsByAgeRange(BST& bst) {
    int startYear, endYear;
    cout << "Enter the starting birth year: ";
    cin >> startYear;
    cout << "Enter the ending birth year: ";
    cin >> endYear;

    cout << "Actors born between " << startYear << " and " << endYear << ":\n";
    bst.displayRange(startYear, endYear);
}

// ----------------------------------------------------------------------
// Feature F: Load movies into BST (already uses parseCSVRow properly)
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
            isFirstLine = false; // Skip header
            continue;
        }

        DynamicArray<std::string> fields;
        parseCSVRow(line, fields);

        // We expect 4 columns: ID, Title, Description, Year
        if (fields.getSize() < 4) {
            cerr << "Error: Malformed row in movies.csv: " << line << endl;
            continue;
        }

        try {
            int id = stoi(fields[0]);
            string title = fields[1];
            // fields[2] is description
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

// ----------------------------------------------------------------------
// Feature F: Display movies from the past three years
// ----------------------------------------------------------------------
void displayMoviesFromPastThreeYears(MovieBST& movieBST) {
    int currentYear = 2025;
    int startYear = currentYear - 3;

    cout << "Movies released in the past 3 years (from "
        << startYear << " to " << currentYear << "):\n";
    movieBST.displayInRange(startYear, currentYear);
}

// ----------------------------------------------------------------------
// Feature G: Display all movies an actor starred in (in alphabetical order)
// ----------------------------------------------------------------------
// Helper function
// A simple insertion sort for DynamicArray<string> 
void sortTitles(DynamicArray<std::string>& titles) {
    for (int i = 1; i < titles.getSize(); ++i) {
        std::string currentTitle = titles[i];
        int j = i - 1;

        // Move elements that are greater than currentTitle one step right
        while (j >= 0 && titles[j] > currentTitle) {
            titles[j + 1] = titles[j];
            j--;
        }
        // Insert currentTitle at the correct spot
        titles[j + 1] = currentTitle;
    }
}

// Feature G: Display all movies an actor starred in (in alphabetical order)
void displayMoviesByActor(
    int actorId,
     HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, Movie>& movieTable
) {
    // 1) Retrieve the movie ID list for this actor:
    const DynamicArray<int>* movies = actorToMovies.get(actorId);
    if (!movies) {
        std::cout << "Actor ID " << actorId << " not found or has no movies.\n";
        return;
    }

    // 2) Gather movie titles into a temporary DynamicArray<string>:
    DynamicArray<std::string> movieTitles;
    for (int i = 0; i < movies->getSize(); ++i) {
        int movieId = (*movies)[i];
        Movie* moviePtr = movieTable.get(movieId);
        if (moviePtr) {
            movieTitles.pushBack(moviePtr->getTitle());
        }
    }

    // 3) Sort the collected titles in ascending alphabetical order
    sortTitles(movieTitles);

    // 4) Print them out
    if (movieTitles.getSize() == 0) {
        std::cout << "Actor ID " << actorId << " has no valid movies or does not exist.\n";
        return;
    }

    std::cout << "Movies starred by Actor ID " << actorId << ":\n";
    for (int i = 0; i < movieTitles.getSize(); ++i) {
        std::cout << " - " << movieTitles[i] << "\n";
    }
}

// ----------------------------------------------------------------------
// Feature H: Display all the actors in a particular movie (in alphabetical order)
// ----------------------------------------------------------------------
// A simple insertion sort for a DynamicArray<string>
void sortNames(DynamicArray<std::string>& names) {
    for (int i = 1; i < names.getSize(); ++i) {
        std::string current = names[i];
        int j = i - 1;
        // Move elements that are greater than 'current' one step right
        while (j >= 0 && names[j] > current) {
            names[j + 1] = names[j];
            j--;
        }
        names[j + 1] = current;
    }
}

// Feature H: Display all the actors in a particular movie (in alphabetical order)
// Displays all actors in a given movie, sorted alphabetically by actor name.
void displayActorsByMovie(
    int movieId,
    HashTable<int, DynamicArray<int>>& movieToActors,
    HashTable<int, Actor>& actorTable
) {
    // 1) Retrieve the list of actor IDs for this movie:
    const DynamicArray<int>* actorList = movieToActors.get(movieId);
    if (!actorList) {
        std::cout << "Movie ID " << movieId << " not found or has no actors.\n";
        return;
    }

    // 2) Gather actor names into a temporary DynamicArray<string>:
    DynamicArray<std::string> actorNames;
    for (int i = 0; i < actorList->getSize(); ++i) {
        int actorId = (*actorList)[i];
        const Actor* actorPtr = actorTable.get(actorId);
        if (actorPtr) {
            actorNames.pushBack(actorPtr->getName());
        }
    }

    // 3) Sort the collected names in ascending (alphabetical) order:
    sortNames(actorNames);

    // 4) Print them out
    if (actorNames.getSize() == 0) {
        std::cout << "Movie ID " << movieId << " has no valid actors or does not exist.\n";
        return;
    }

    std::cout << "Actors in Movie ID " << movieId << ":\n";
    for (int i = 0; i < actorNames.getSize(); ++i) {
        std::cout << " - " << actorNames[i] << "\n";
    }
}


// ----------------------------------------------------------------------
// Feature I: Display a list of all actors that a particular actor knows.
// ----------------------------------------------------------------------
// Searching algorithm: depth-first search
// Recursive DFS helper
void dfsKnownActors(
    int currentActorId,
    int depth,
    int maxDepth,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    DynamicArray<int>& visited,      // to avoid cycles
    DynamicArray<int>& results       // store known actor IDs
) {
    if (depth >= maxDepth) {
        return;
    }

    // For each movie that currentActorId is in:
    DynamicArray<int>* movies = actorToMovies.get(currentActorId);
    if (!movies) return; // no movies for this actor

    for (int i = 0; i < movies->getSize(); ++i) {
        int movieId = (*movies)[i];

        // For each actor that shares this movie:
        DynamicArray<int>* coActors = movieToActors.get(movieId);
        if (!coActors) continue;

        for (int j = 0; j < coActors->getSize(); ++j) {
            int coActorId = (*coActors)[j];

            // If not visited, mark visited & add to results
            bool alreadyVisited = false;
            for (int k = 0; k < visited.getSize(); k++) {
                if (visited[k] == coActorId) {
                    alreadyVisited = true;
                    break;
                }
            }
            if (!alreadyVisited && coActorId != currentActorId) {
                visited.pushBack(coActorId);
                results.pushBack(coActorId);

                // Recurse to get coActors-of-coActors if depth+1 < maxDepth
                dfsKnownActors(coActorId, depth + 1, maxDepth,
                    actorToMovies, movieToActors,
                    visited, results);
            }
        }
    }
}
// Main function to get known actors (distance ≤ 2) from a given actor
void getKnownActorsDFS(
    int startActorId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    DynamicArray<int>& results
) {
    // visited IDs 
    DynamicArray<int> visited;

    // Mark the starting actor as visited
    visited.pushBack(startActorId);
    int maxDepth = 2;

    // Start DFS from startActorId, with depth=0
    dfsKnownActors(startActorId, 0, maxDepth,
        actorToMovies, movieToActors,
        visited, results);
}

// Feature I: Display a list of all actors that a particular actor knows.
void displayKnownActors(
    int startActorId,
    HashTable<int, DynamicArray<int>>& actorToMovies,
    HashTable<int, DynamicArray<int>>& movieToActors,
    HashTable<int, Actor>& actorTable
) {
    // 1) Gather all known actor IDs within 2 levels
    DynamicArray<int> knownIds;
    getKnownActorsDFS(startActorId, actorToMovies, movieToActors, knownIds);

    // 2) Convert to actor names
    DynamicArray<std::string> knownNames;
    for (int i = 0; i < knownIds.getSize(); ++i) {
        Actor* aPtr = actorTable.get(knownIds[i]);
        if (aPtr) {
            knownNames.pushBack(aPtr->getName());
        }
    }

    // 3) Sort by name (simple insertion sort)
    for (int i = 1; i < knownNames.getSize(); ++i) {
        std::string key = knownNames[i];
        int j = i - 1;
        while (j >= 0 && knownNames[j] > key) {
            knownNames[j + 1] = knownNames[j];
            j--;
        }
        knownNames[j + 1] = key;
    }

    // 4) Print
    std::cout << "Actors that " << startActorId << " knows (up to 2 hops):\n";
    for (int i = 0; i < knownNames.getSize(); ++i) {
        std::cout << " - " << knownNames[i] << "\n";
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

    // Admin workflow
    if (role == "admin") {
        while (true) {
            displayAdminMenu();
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "Add new actor \n";
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
                cout << "Add new movie \n";
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
                cout << "Add actor to movie \n";
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
    // User workflow
    else if (role == "user") {
        // Load actors into BST for user features
        loadActorsToBST(actorTable, actorBST);

        while (true) {
            displayUserMenu();
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "Display actors in age range \n";
                displayActorsByAgeRange(actorBST);
            }
            else if (choice == 2) {
                cout << "Display movies made within past 3 years\n";
                displayMoviesFromPastThreeYears(movieBST);
            }
            else if (choice == 3) {
                cout << "Display movies an Actor starred in\n";
                int actorId;
                std::cout << "\nEnter Actor ID: ";
                std::cin >> actorId;

                // Call our new function
                displayMoviesByActor(actorId, actorToMovies, movieTable);
            }
            else if (choice == 4) {
                cout << "Display actors in a particular movie\n";
                int movieId;
                std::cout << "\nEnter Movie ID: ";
                std::cin >> movieId;

                // Call our new function
                displayActorsByMovie(movieId, movieToActors, actorTable);
            }
            else if (choice == 5) {
                cout << "Display a list of all actors that a particular actor knows.\n";
                int actorId;
                std::cout << "Enter Actor ID: ";
                std::cin >> actorId;
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
    // Invalid role
    else {
        cout << "\nInvalid role entered. Exiting program...\n";
    }

    return 0;
}
