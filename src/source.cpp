#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <thread>
#include <limits>
#include "C:\DataBaseCpp\src\headers\createUser.h"
#include "C:\DataBaseCpp\src\headers\authUser.h"

using namespace std;

struct dataBase {
    string name;
    int ID;
    float price;
};

vector<dataBase> myDataBase;

void printData() {
    cout << "INFO: " << endl;
    for (const auto& product : myDataBase) {
        cout << "Product name: " << product.name << endl;
        cout << "Product ID: " << product.ID << endl;
        cout << "Product price: " << product.price << endl << endl;
    }
}

void enterData() {
    dataBase newProduct;
    cout << "Enter name of product: ";
    cin >> newProduct.name;
    cout << "Enter ID of product: ";
    cin >> newProduct.ID;
    cout << "Enter the price of product: ";
    cin >> newProduct.price;
    myDataBase.push_back(newProduct);
    cout << "Product created successfully!" << endl;
}

void saveDataToFile() {
    ofstream outFile("C:\\DataBaseCpp\\data\\configs\\user.cfg");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    outFile << myDataBase.size() << endl;
    for (const auto& product : myDataBase) {
        outFile << product.name << endl;
        outFile << product.ID << endl;
        outFile << product.price << endl;
    }
    outFile.close();
    cout << "Data saved successfully!" << endl;
}

void deleteDataFromFile() {
    ofstream outFile("C:\\DataBaseCpp\\data\\configs\\user.cfg");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    outFile << 0 << endl;
    outFile.close();
}


void loadDataFromFile() {
    ifstream inFile("C:\\DataBaseCpp\\data\\configs\\user.cfg");
    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    size_t productCount;
    inFile >> productCount;
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    myDataBase.resize(productCount);
    for (auto& product : myDataBase) {
        getline(inFile, product.name);
        inFile >> product.ID;
        inFile >> product.price;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    inFile.close();
    cout << "Data loaded successfully!" << endl;
}

int main() {

    loadDataFromFile();
    
    char choiceStart;
    char choice;

    cout << "WELCOME TO DATABASE-ULTRA 0.1: " << endl;
    cout << "Choose action: (a - Authentificate user, c - Create new user, q - Continue to Database)" << endl;
    cin >> choiceStart;

    if (choiceStart == 'a') {
        userAuth();
    }
    else if (choiceStart == 'c') {
        userCreate();
    }
    else if (choiceStart == 'q') {
        goto start;
    }
    
    start:
    while (true) {
        cout << endl << "Choose action: (0 - Display products, 1 - Create product, 2 - Save products, d - Delete data, q - Quit)" << endl;
        cin >> choice;
        cout << endl;
        if (choice == '0') {
            printData();
        } 
        else if (choice == '1') {
            enterData();
        } 
        else if (choice == '2') {
            saveDataToFile();
        } 
        else if (choice == 'q') {
            cout << "GOODBYE!" << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            exit(0);
        }
        else if (choice == 'd') {
            deleteDataFromFile();
            cout << "Data deleted successfully!" << endl;
        } 
        else {
            cout << "Unknown operation! Try Again!" << endl;
        }
    }

    saveDataToFile();

    return 0;
}