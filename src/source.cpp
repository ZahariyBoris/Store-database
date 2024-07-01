#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct dataBase {
    char name[20];
    int ID;
    float price;
};

dataBase myDataBase[10];
int productCount = 0;
const int MAX_ATTEMPTS = 3;
const int PASSWORD = 901090;

void printData() {
    cout << "INFO: " << endl;
    for (int i = 0; i < productCount; i++) {
        cout << "Product name: " << myDataBase[i].name << endl;
        cout << "Product ID: " << myDataBase[i].ID << endl;
        cout << "Product price: " << myDataBase[i].price << endl << endl;
    }
}

void enterData() {
    cout << "Enter name of product: ";
    cin >> myDataBase[productCount].name;
    cout << "Enter ID of product: ";
    cin >> myDataBase[productCount].ID;
    cout << "Enter the price of product: ";
    cin >> myDataBase[productCount].price;
    productCount++;
    cout << "Product created successfully!" << endl;
}

void saveDataToFile() {
    ofstream outFile("C:\\DataBaseCpp\\data\\data.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    outFile << productCount << endl;
    for (int i = 0; i < productCount; i++) {
        outFile << myDataBase[i].name << endl;
        outFile << myDataBase[i].ID << endl;
        outFile << myDataBase[i].price << endl;
    }
    outFile.close();
    cout << "Data saved successfully!" << endl;
}

void loadDataFromFile() {
    ifstream inFile("C:\\DataBaseCpp\\data\\data.txt");
    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    inFile >> productCount;
    inFile.ignore();
    for (int i = 0; i < productCount; i++) {
        inFile.getline(myDataBase[i].name, 20);
        inFile >> myDataBase[i].ID;
        inFile >> myDataBase[i].price;
        inFile.ignore();
    }
    inFile.close();
    cout << "Data loaded successfully!" << endl;
}

void deleteDataFromFile() {
    ofstream outFile("C:\\DataBaseCpp\\data\\data.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    productCount = 0;
    outFile << productCount << endl;
    outFile.close();
}

bool checkPassword() {
    int password;
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        cout << "Enter password: ";
        cin >> password;
        if (password == PASSWORD) {
            return true;
        } else {
            cout << "Wrong password! ";
            if (attempt < MAX_ATTEMPTS) {
                cout << "Try Again!" << endl;
            } else {
                cout << "Maximum attempts reached. Exiting program." << endl;
            }
        }
    }
    return false;
}

int main() {
    
    if (checkPassword()) {
        loadDataFromFile();
        int amount;
        char choice;
        while (true) {
            cout << endl << "Choose action: (0 - Display products, 1 - Create product, 2 - Save products, d - Delete data, q - Quit)" << endl;
            cin >> choice;
            cout << endl;
            if (choice == '0') {
                printData();
            } 
            else if (choice == '1') {
                if (productCount < 10) {
                    enterData();
                } 
                else {
                    cout << "Maximum number of products reached!" << endl;
                }
            }
            else if (choice == '2') {
                saveDataToFile();
            }
            else if (choice == 'q') {
                cout << "Goodbye!" << endl;
                break;
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
    }

    return 0;
}