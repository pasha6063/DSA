#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
using namespace std;

class Contact {
public:
    string name;
    string number;
    string email;
    string type;

    Contact(string name = "", string number = "", string email = "", string type = "") 
        : name(name), number(number), email(email), type(type) {}

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << "\nName: " << contact.name
           << "\nNumber: " << contact.number
           << "\nEmail: " << contact.email
           << "\nType: " << contact.type << endl;
        return os;
    }
};

// Node class for Binary Search Tree (BST)
class Node {
public:
    Contact contact;
    Node* left;
    Node* right;

    Node(Contact contact) : contact(contact), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

// Binary Search Tree (BST) class to store contacts
class BST {
private:
    Node* root;

    Node* insert(Node* node, Contact contact) {
        if (node == nullptr) {
            return new Node(contact);
        }

        if (contact.name < node->contact.name) {
            node->left = insert(node->left, contact);
        } else if (contact.name > node->contact.name) {
            node->right = insert(node->right, contact);
        } else {
            if (contact.number != node->contact.number || contact.email != node->contact.email) {
                node->right = insert(node->right, contact);
            } else {
                cout << "\nContact already exists with the same name, number, and email.\n";
            }
        }
        return node;
    }

    Node* search(Node* node, const string& name, const string& number = "", const string& email = "") const {
        if (node == nullptr) return nullptr;

        if (node->contact.name == name && 
            (number.empty() || node->contact.number == number) && 
            (email.empty() || node->contact.email == email)) {
            return node;
        }
        if (name < node->contact.name) {
            return search(node->left, name, number, email);
        }
        return search(node->right, name, number, email);
    }

    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->contact;
        inOrder(node->right);
    }

    Node* deleteNode(Node* node, const string& name) {
        if (node == nullptr) return node;

        if (name < node->contact.name) {
            node->left = deleteNode(node->left, name);
        } else if (name > node->contact.name) {
            node->right = deleteNode(node->right, name);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->contact = temp->contact;
            node->right = deleteNode(node->right, temp->contact.name);
        }
        return node;
    }

    Node* minValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void suggestContacts(Node* node, const string& prefix) const {
        if (node == nullptr) return;
        if (node->contact.name.substr(0, prefix.size()) == prefix) {
            cout << node->contact.name << endl;
        }
        suggestContacts(node->left, prefix);
        suggestContacts(node->right, prefix);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        delete root;
    }

    bool isValidEmail(const string& email) const {
        return email.size() > 10 && email.substr(email.size() - 10) == "@gmail.com";
    }

    void insert(Contact contact) {
        root = insert(root, contact);
    }

    bool contactExists(const string& name, const string& number, const string& email) const {
        return search(root, name, number, email) != nullptr;
    }

    void searchContact(const string& name) const {
        Node* result = search(root, name);
        if (result) {
            cout << "\nContact found:\n" << result->contact;
        } else {
            cout << "\nNo contact found with the name " << name << endl;
        }
    }

    void suggestContacts(const string& prefix) const {
        cout << "\nSuggestions for \"" << prefix << "\":\n";
        suggestContacts(root, prefix);
    }

    void deleteContact(const string& name) {
        root = deleteNode(root, name);
        cout << "\nContact deleted (if it existed).\n";
    }

    void displayAllContacts() const {
        if (root == nullptr) {
            cout << "\nNo contacts available.\n";
        } else {
            cout << "\nDisplaying all contacts:\n";
            inOrder(root);
        }
    }
};

// Application class that manages user interaction
class PhoneBookApp {
private:
    BST bst;
    string password;

    bool authenticate() {
        int attempts = 0;
        string inputPassword;
        while (attempts < 3) {
            cout << "\nEnter password: ";
            getline(cin, inputPassword);
            if (inputPassword == password) {
                return true;
            } else {
                cout << "\nIncorrect password. Try again.\n";
                attempts++;
            }
        }
        cout << "\nToo many failed attempts. Exiting program.\n";
        return false;
    }

    void changePassword() {
        string oldPassword, newPassword;
        cout << "\nEnter old password: ";
        getline(cin, oldPassword);
        if (oldPassword == password) {
            cout << "\nEnter new password: ";
            getline(cin, newPassword);
            password = newPassword;
            cout << "\nPassword changed successfully!\n";
        } else {
            cout << "\nIncorrect old password.\n";
        }
    }

public:
    PhoneBookApp() : password("123") {}

    void startApp() {
        if (authenticate()) {
            string choice;
            do {
                displayMenu();
                getline(cin, choice);
                if (choice == "1") {
                    system("cls");
                    addContact();
                } else if (choice == "2") {
                    system("cls");
                    editContact();
                } else if (choice == "3") {
                    system("cls");
                    searchContact();
                } else if (choice == "4") {
                    system("cls");
                    deleteContact();
                } else if (choice == "5") {
                    system("cls");
                    displayAllContacts();
                } else if (choice == "6") {
                    system("cls");
                    changePassword();
                }
            } while (choice != "0");
        }
    }

    void addContact() {
        string name, number, email, type;

        cout << "\nEnter name: ";
        getline(cin, name);

        cout << "Enter number: ";
        getline(cin, number);

        while (true) {
            cout << "Enter email (must end with '@gmail.com'): ";
            getline(cin, email);
            if (bst.isValidEmail(email)) {
                break;
            } else {
                cout << "\nInvalid email. Please ensure the email ends with '@gmail.com'.\n";
            }
        }

        cout << "Enter type (PTCL, Local, Emergency): ";
        getline(cin, type);

        if (bst.contactExists(name, number, email)) {
            cout << "\nA contact with the same name, number, and email already exists.\n";
        } else {
            Contact newContact(name, number, email, type);
            bst.insert(newContact);
            cout << "\nContact added successfully!\n";
        }
    }

    void searchContact() {
        string name;
        cout << "\nEnter the name of the contact to search (or partial name for suggestions): ";
        getline(cin, name);

        bst.suggestContacts(name);  // Display suggestions based on input
        bst.searchContact(name);    // Exact search
    }

    void deleteContact() {
        string name;
        cout << "\nEnter the name of the contact to delete: ";
        getline(cin, name);
        bst.deleteContact(name);
    }

    void editContact() {
        string name;
        cout << "\nEnter the name of the contact to edit: ";
        getline(cin, name);
        bst.deleteContact(name);
        addContact();
    }

    void displayAllContacts() {
        bst.displayAllContacts();
    }

    void displayMenu() const {
        cout << "\n\n\t__________ Phone Book Menu __________\n";
        cout << "\t1. Add Contact\n";
        cout << "\t2. Edit Contact\n";
        cout << "\t3. Search Contact\n";
        cout << "\t4. Delete Contact\n";
        cout << "\t5. Display All Contacts\n";
        cout << "\t6. Change Password\n";
        cout << "\t0. Exit\n";
        cout << "\tEnter your choice: ";
    }
};

int main() {
    PhoneBookApp app;
    app.startApp();
    return 0;
}
