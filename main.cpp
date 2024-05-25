#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Bus {
    int number;
    string driverName;
    int routeNumber;
    int seats;
    Bus* left;
    Bus* right;

    Bus(int num, string name, int route, int seats) : number(num), driverName(name), routeNumber(route), seats(seats), left(nullptr), right(nullptr) {}
};

Bus* insertBus(Bus* root, int number, string driverName, int routeNumber, int seats) {
    if (root == nullptr) {
        return new Bus(number, driverName, routeNumber, seats);
    }

    if (number < root->number) {
        root->left = insertBus(root->left, number, driverName, routeNumber, seats);
    }
    else {
        root->right = insertBus(root->right, number, driverName, routeNumber, seats);
    }

    return root;
}

Bus* searchBus(Bus* root, int number) {
    if (root == nullptr || root->number == number) {
        return root;
    }

    if (number < root->number) {
        return searchBus(root->left, number);
    }
    else {
        return searchBus(root->right, number);
    }
}

void inorderTraversal(Bus* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "Number: " << root->number << ", Driver: " << root->driverName << ", Route: " << root->routeNumber << ", Seats: " << root->seats << endl;
        inorderTraversal(root->right);
    }
}

void writeToFile(Bus* root, ofstream& outFile) {
    if (root != nullptr) {
        writeToFile(root->left, outFile);
        outFile << "Number: " << root->number << ", Driver: " << root->driverName << ", Route: " << root->routeNumber << ", Seats: " << root->seats << endl;
        writeToFile(root->right, outFile);
    }
}

int main() {
    Bus* root = nullptr;

    int choice;
    do {
        cout << "\nBus Park Management System\n";
        cout << "1. Add a new bus\n";
        cout << "2. Search for a bus\n";
        cout << "3. Display all buses\n";
        cout << "4. Write buses to file\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int num, route, seats;
            string name;
            cout << "Enter bus number: ";
            cin >> num;
            cout << "Enter driver name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter route number: ";
            cin >> route;
            cout << "Enter number of seats: ";
            cin >> seats;
            root = insertBus(root, num, name, route, seats);
            cout << "Bus added successfully!\n";
            break;
        }
        case 2: {
            int num;
            cout << "Enter bus number to search: ";
            cin >> num;
            Bus* foundBus = searchBus(root, num);
            if (foundBus != nullptr) {
                cout << "Bus found!\n";
                cout << "Number: " << foundBus->number << ", Driver: " << foundBus->driverName << ", Route: " << foundBus->routeNumber << ", Seats: " << foundBus->seats << endl;
            }
            else {
                cout << "Bus not found!\n";
            }
            break;
        }
        case 3: {
            cout << "List of all buses:\n";
            inorderTraversal(root);
            break;
        }
        case 4: {
            ofstream outFile("bus_info.txt");
            if (!outFile) {
                cout << "Error opening file!\n";
            }
            else {
                cout << "Writing buses to file...\n";
                writeToFile(root, outFile);
                outFile.close();
                cout << "Buses written to file successfully!\n";
            }
            break;
        }
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
