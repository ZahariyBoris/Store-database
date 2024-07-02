#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

void userAuth() {
    string token;
    int password;

    string lineToken;
    string linePassword;

    bool tokenFound = false;
    bool passwordFound = false;

    cout << "PLEASE LOG IN: " << endl;
    cout << "Enter your token: ";
    cin >> token;

    ifstream file("C:\\DataBaseCpp\\data\\configs\\user.cfg");
    
    while (getline(file, lineToken)) {
        if (lineToken == token) {
            tokenFound = true;
            break;
        }
    }

    if (tokenFound == true) {
        cout << "Key found!" << endl;
    }
    else {
        cout << "Key not found!" << endl;
    }

    file.close();

    cout << "Enter your password: ";
    cin >> password;

    ifstream filePass("C:\\DataBaseCpp\\data\\configs\\user.cfg");

    while (getline(filePass, linePassword)) {
        if (stoi(linePassword) == password) {
            passwordFound = true;
            break;
        }
    }

    if (passwordFound == true) {
        cout << "Password found!" << endl;
    }
    else {
        cout << "Password not found!" << endl;
    }
}