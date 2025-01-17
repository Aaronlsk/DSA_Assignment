// main.cpp
#include <iostream>
#include "HashTable.h"

void displayMenu() {
    cout << "1. Add New Actor\n";
    cout << "2. Get Actor by ID\n";
    cout << "3. Remove Actor\n";
    cout << "4. Exit\n";
}

int main() {
    HashTable hashTable(10); // Create a hash table with capacity 10

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            int id, birthYear;
            string name;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Birth Year: ";
            cin >> birthYear;

            Actor actor(id, name, birthYear);
            if (hashTable.addActor(actor)) {
                cout << "Actor added successfully!\n";
            }
            else {
                cout << "Actor with this ID already exists.\n";
            }
        }
        else if (choice == 2) {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            Actor* actor = hashTable.getActor(id);
            if (actor) {
                cout << "Actor Found: " << actor->getName() << ", Birth Year: " << actor->getBirthYear() << "\n";
            }
            else {
                cout << "Actor not found.\n";
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            if (hashTable.removeActor(id)) {
                cout << "Actor removed successfully!\n";
            }
            else {
                cout << "Actor not found.\n";
            }
        }
        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
