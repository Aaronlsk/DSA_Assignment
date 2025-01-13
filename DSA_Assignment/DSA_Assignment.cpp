#include <iostream>
#include <string>
#include "Actor.h"
#include "List.h"
using namespace std;

// Function prototypes
void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
int calculateAge(const string& dateOfBirth);

int main() {
    cout << "Welcome! Join us fellow movie enthusiasts as we explore \nour favourite actors and movies using this application!" << endl;
    int choice;

    while (true) { // Loop until the user exits
        displayMainMenu();
        cout << "Select your role: ";
        cin >> choice;

        if (choice == 1) {
            displayAdminMenu();
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
void displayAdminMenu() {
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
            // Add functionality here
            List actorList;
            string name;
            string dateOfBirth;
            cout << "Enter name of actor: ";
            cin >> name;
            cout << "Enter the actor's date of birth: ";
            cin >> dateOfBirth;

            int age = calculateAge(dateOfBirth);

            Actor newActor(name, dateOfBirth, age);
            actorList.add(newActor);

            cout << "Actor added successfully!" << endl;
            actorList.print();
        }
        else if (adminChoice == 2) {
            cout << "[2] Add new movie" << endl;
            // Add functionality here
        }
        else if (adminChoice == 3) {
            cout << "[3] Add an actor to a movie" << endl;
            // Add functionality here
        }
        else if (adminChoice == 4) {
            cout << "[4] Update actor/movie details" << endl;
            // Add functionality here
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



// -------------------------- Methods -------------------------
// Function to calculate the actor's age
int calculateAge(const string& dateOfBirth) {
    // Get current date (this will get the system date)
    time_t t = time(0);   // Get current time
    struct tm now;
    localtime_s(&now, &t);  // Using localtime_s to avoid deprecation warning

    // Extract the current year, month, and day
    int currentYear = now.tm_year + 1900;  // tm_year gives years since 1900
    int currentMonth = now.tm_mon + 1;     // tm_mon gives months since January (0-11)
    int currentDay = now.tm_mday;           // tm_mday gives day of the month

    // Parse the date of birth string (assuming it's in "YYYY-MM-DD" format)
    int birthYear, birthMonth, birthDay;
    sscanf_s(dateOfBirth.c_str(), "%d-%d-%d", &birthYear, &birthMonth, &birthDay);  // Using sscanf_s for safety

    // Calculate age based on current date and birth date
    int age = currentYear - birthYear;

    // Adjust age if the current month is before the birth month, or if it's the birth month but the current day is before the birth day
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        age--;
    }

    return age;
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
