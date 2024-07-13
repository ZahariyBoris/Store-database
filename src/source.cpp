#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <typeinfo>

#include "include/createUser.h"
#include "include/authUser.h"
#include "include/idGenerator.h"

using namespace std;

enum class SortOption {
    NAME,
    ID,
    PRICE,
    NONE
};

struct Product {
    string name;
    int ID;
    float price;
};

vector<Product> myDataBase;

const string productFilename = "../data/database.csv";
const string userFilename = "../config/user.cfg";

void loadDataFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading: " << filename << endl;
        return;
    }

    myDataBase.clear();
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int ID;
        float price;

        getline(ss, name, ',');
        ss >> ID;
        ss.ignore(1);
        ss >> price;

        myDataBase.push_back({name, ID, price});
    }

    inFile.close();
    cout << "Data loaded successfully from file: " << filename << endl;
}

void printData(SortOption sortOption) {
    if (myDataBase.empty()) {   
        cout << "No products to display." << endl;
        return;
    }

    switch (sortOption) {
        case SortOption::NAME:
            sort(myDataBase.begin(), myDataBase.end(), [](const Product& a, const Product& b) {
                return a.name < b.name;
            });
            break;
        case SortOption::ID:
            sort(myDataBase.begin(), myDataBase.end(), [](const Product& a, const Product& b) {
                return a.ID < b.ID;
            });
            break;
        case SortOption::PRICE:
            sort(myDataBase.begin(), myDataBase.end(), [](const Product& a, const Product& b) {
                return a.price < b.price;
            });
            break;
        case SortOption::NONE:
        default:
            break;
    }

    cout << "---------------------------------------" << endl;
    cout << "|   Name   |      ID      |   Price   |" << endl;
    cout << "---------------------------------------" << endl;
    for (const auto& product : myDataBase) {
        cout << "|" << setw(9) << product.name << " |"
             << setw(13) << product.ID << " |"
             << setw(10) << product.price << " |" << endl;
    }
    cout << "---------------------------------------" << endl << endl;
}

void enterData() {
    while (true) {
        Product newProduct;

        cout << "\nEnter name of product: ";
        getline(cin, newProduct.name);

        if (newProduct.name.empty()) {
            cout << "Invalid input. Please try again!" << endl;
            continue;
        }

        newProduct.ID = generateID();

        cout << "Enter the price of product: ";
        if (!(cin >> newProduct.price) || typeid(newProduct.price) != typeid(float)) {
            cout << "Invalid input. Please try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        myDataBase.push_back(newProduct);
        cout << "Product created successfully!" << endl;
        break;
    }
}

void saveDataToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& product : myDataBase) {
        outFile << product.name << "," << product.ID << "," << product.price << endl;
    }

    outFile.close();
    cout << "Data saved successfully to file: " << filename << endl;
}

void deleteDataFromFile(const string& filename1) {
    ofstream outFile1(filename1, ofstream::trunc);
    if (!outFile1) {
        cerr << "Error opening file for writing: " << filename1 << endl;
        return;
    }
    outFile1.close();
    cout << "Data deleted successfully from file: " << filename1 << endl;
}

bool userExists(const string& filename, const string& login) {
    ifstream inFile(filename);
    if (!inFile) {
        return false;
    }

    string fileLogin;
    while (inFile >> fileLogin) {
        if (fileLogin == login) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

int main() {
    
    char choice;
    string login, password;

    cout << "---------------------------------" << endl;
    cout << "| WELCOME TO DATABASE-ULTRA 0.1 |" << endl;
    cout << "---------------------------------";

    while (true) {
        cout << endl << "Choose action:" << endl;
        cout << "c - Create new user" << endl;
        cout << "a - Authenticate user" << endl;
        cout << "q - Quit" << endl;
        cout << "Enter your choice: ";
        
        cin >> choice;
        
        switch (choice) {
            case 'c':
                createUser(userFilename);
                this_thread::sleep_for(chrono::milliseconds(999));
                system("cls");
                break;
            case 'a':
                system("cls");
                cout << endl << "Enter login: ";
                cin >> login;
                cout << "Enter password: ";
                cin >> password;

                if (authenticateUser(userFilename, login, password)) {
                    cout << "Authentication successful! Welcome, " << login << "!" << endl;

                    loadDataFromFile(productFilename);
                    this_thread::sleep_for(chrono::milliseconds(700));
                    system("cls");

                    while (true) {
                        cout << endl << "Choose action:" << endl;
                        cout << "1 - Display products" << endl;
                        cout << "2 - Create product" << endl;
                        cout << "3 - Delete all data (User and products)" << endl;
                        cout << "4 - Delete only data" << endl;
                        cout << "q - Quit" << endl;
                        cout << "Enter your choice: ";

                        cin >> choice;

                        switch (choice) {
                            case '1': {
                                system("cls");
                                char sortChoice;
                                cout << "Sort by: (n)ame, (i)d, (p)rice, (e)xit: ";
                                cin >> sortChoice;
                                SortOption sortOption = SortOption::NONE;
                                switch (sortChoice) {
                                    case 'n':
                                        sortOption = SortOption::NAME;
                                        break;
                                    case 'i':
                                        sortOption = SortOption::ID;
                                        break;
                                    case 'p':
                                        sortOption = SortOption::PRICE;
                                        break;
                                    case 'e':
                                        sortOption = SortOption::NONE;
                                        break;
                                    default:
                                        cout << "Invalid choice. Defaulting to no sorting." << endl;
                                        sortOption = SortOption::NONE;
                                        break;
                                }
                                printData(sortOption);
                                break;
                            }
                            case '2':
                                system("cls");
                                enterData();
                                saveDataToFile(productFilename);
                                break;
                            case '3':
                                deleteDataFromFile(productFilename);
                                deleteDataFromFile(userFilename);
                                break;
                            case '4':
                                deleteDataFromFile(productFilename);
                                break;
                            case 'q':
                                cout << "Goodbye!" << endl;
                                this_thread::sleep_for(chrono::milliseconds(500));
                                exit(0);
                            default:
                                cout << "Invalid choice. Try again." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                        }
                    }
                } else {
                    cout << "Authentication failed. Please try again." << endl;
                }
                break;
            case 'q':
                cout << "Goodbye!" << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}