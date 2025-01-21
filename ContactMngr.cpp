#include "RedBlackTree.h"

#include <iostream>
using namespace std;

void displayMenu() {
    cout << "\n=============================\n";
    cout << " Contact Management System\n";
    cout << "=============================\n";
    cout << "1. Add Contact\n";
    cout << "2. Search Contact\n";
    cout << "3. Delete Contact\n";
    cout << "4. List All Contacts\n";
    cout << "5. Visualize Tree\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    RedBlackTree tree;
    int choice;
    string name, phone;
    tree.insertRomanianContacts();
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter contact name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter phone number: ";
            getline(cin, phone);
            tree.insert(name, phone);
            cout << "Contact added successfully.\n";
            break;

        case 2:
            cout << "Enter name to search: ";
            cin.ignore();
            getline(cin, name);
            phone = tree.search(name);
            if (phone.empty()) {
                cout << "Contact not found.\n";
            }
            else {
                cout << "Name: " << name << ", Phone: " << phone << "\n";
            }
            break;

        case 3:
            cout << "Enter name to delete: ";
            cin.ignore();
            getline(cin, name);
            tree.remove(name);
            cout << "Contact deleted successfully.\n";
            break;

        case 4: 
            cout << "Contact List:\n";
            tree.listContacts();
            break;
        case 5: 
			tree.visualizeTree();
			break;
        case 6: 
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}
