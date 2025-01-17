#include <iostream>
#include "ActorHashTable.h"
#include "MovieHashTable.h"

void displayAdminMenu() {
    cout << "1. Add New Actor\n";
    cout << "2. Add New Movie\n";
    cout << "3. Update Actor Details\n";
    cout << "4. Update Movie Details\n";
    cout << "5. Display All Data (Debugging)\n";
    cout << "6. Exit\n";
}

// Function to print all actors in the hash table
void displayAllActors(ActorHashTable& actorTable) {
    cout << "Actors:\n";
    for (int i = 0; i < 10; ++i) { // Loop through hash table buckets
        auto& bucket = actorTable.getBucket(i); // Get the bucket (requires adding getBucket())
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
        auto& bucket = movieTable.getBucket(i); // Get the bucket (requires adding getBucket())
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
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
