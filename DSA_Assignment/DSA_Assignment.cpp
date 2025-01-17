#include <iostream>
#include <string>
#include "Actor.h"
#include "Movie.h"
#include "List.h"
using namespace std;

// Function prototypes
void displayMainMenu();
void displayAdminMenu(List<Actor>& actorList, List<Movie>& movieList);
void displayUserMenu();

int main() {
    List<Actor> actorList;
    actorList.readFromCSV("actors.csv");

    List<Movie> movieList;
    movieList.readFromCSV("movies.csv");

    cout << "Welcome! Join us fellow movie enthusiasts as we explore \nour favourite actors and movies using this application!" << endl;
    int choice;

    while (true) { // Loop until the user exits
        displayMainMenu();
        cout << "Select your role: ";
        cin >> choice;

        if (choice == 1) {
            displayAdminMenu(actorList, movieList);
        }
        else if (choice == 2) {
            displayUserMenu();
        }
        else if (choice == 0) {
            cout << "Exiting the application. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

// Function to display the main menu
void displayMainMenu() {
    cout << "\n---------------- Main Menu -------------------" << endl;
    cout << "[1] Administrator" << endl;
    cout << "[2] User" << endl;
    cout << "[0] Exit" << endl;
    cout << "----------------------------------------------" << endl;
}

// Function to display the administrator menu
void displayAdminMenu(List<Actor>& actorList, List<Movie>& movieList) {
    int adminChoice;
    while (true) {
        cout << "\n--------------- Administrator Menu ---------------" << endl;
        cout << "[1] Add new actor" << endl;
        cout << "[2] Add new movie" << endl;
        cout << "[3] Add an actor to a movie" << endl;
        cout << "[4] Update actor/movie details" << endl;
        cout << "[0] Return to main menu" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Enter your option: ";
        cin >> adminChoice;

        if (adminChoice == 1) {
            cout << "[1] Add new actor" << endl;

            int id;
            string name;
            int birthYear;

            cout << "Enter id of actor: ";
            cin >> id;
            cin.ignore();

            cout << "Enter name of actor: ";
            getline(cin, name);

            cout << "Enter the actor's year of birth: ";
            cin >> birthYear;

            // Add the new actor
            Actor newActor(id, name, birthYear);
            actorList.add(newActor);

            cout << "Actor " << newActor.getName() << "has been added successfully!" << endl;
            actorList.print();
        }
        else if (adminChoice == 2) {
            cout << "[2] Add new movie" << endl;
            // Add functionality here
            int id;
            string title;
            int year;

            cout << "Enter id of movie: ";
            cin >> id;
            cin.ignore();

            cout << "Enter name of movie: ";
            getline(cin, title);

            cout << "Enter the movie's year of release: ";
            cin >> year;

            // Add the new movie
            Movie newMovie(id, title, year);
            movieList.add(newMovie);

            cout << "Movie " << newMovie.getTitle() << " has been added successfully!" << endl;
            movieList.print();
        }
        else if (adminChoice == 3) {
            cout << "[3] Add an actor to a movie" << endl;
            // Add functionality here
        }
        else if (adminChoice == 4) {
            cout << "[4] Update actor/movie details" << endl;
            // Add functionality here
            int choice;
            cout << "\n----------- Menu -----------" << endl;
            cout << "[1] Update actor details" << endl;
            cout << "[2] Update movie details" << endl;
            cout << "Select your choice: ";
            cin >> choice;


            if (choice == 1) {
                cout << "[1] Update actor details" << endl;
                // Add functionality here
            }
            else if (choice == 2) {
                cout << "[2] Update movie details" << endl;
                // Add functionality here
            }
            else if (choice == 0) {
                cout << "Returning to Admin Menu!" << endl;
                break;
            }
        }
        else if (adminChoice == 0) {
            cout << "Returning to main menu..." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Function to display the user menu
void displayUserMenu() {
    int userChoice;
    while (true) {
        cout << "\n------------------- User Menu -------------------" << endl;
        cout << "[1] Display the actors in an age range" << endl;
        cout << "[2] Display movies made within the past 3 years" << endl;
        cout << "[3] Display all movies an actor starred in" << endl;
        cout << "[4] Display all the actors in a particular movie" << endl;
        cout << "[5] Display a list of all actors that a particular actor knows" << endl;
        cout << "[0] Return to main menu" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Enter your option: ";
        cin >> userChoice;

        if (userChoice == 1) {
            cout << "[1] Display the actors in an age range" << endl;
            // Add functionality here
        }
        else if (userChoice == 2) {
            cout << "[2] Display movies made within the past 3 years" << endl;
            // Add functionality here
        }
        else if (userChoice == 3) {
            cout << "[3] Display all movies an actor starred in" << endl;
            // Add functionality here
        }
        else if (userChoice == 4) {
            cout << "[4] Display all the actors in a particular movie" << endl;
            // Add functionality here
        }
        else if (userChoice == 5) {
            cout << "[5] Display a list of all actors that a particular actor knows" << endl;
            // Add functionality here
        }
        else if (userChoice == 0) {
            cout << "Returning to Main Menu..." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}
