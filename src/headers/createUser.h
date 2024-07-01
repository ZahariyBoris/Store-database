#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

struct infoNewUser {
    string token;
    int password;
};

vector<infoNewUser> newUser;

void userCreate() {
    string token = "";
    int password;
    
    cout << "CREATE NEW USER: " << endl;
    cout << "Enter your token: ";
    cin >> token;
    cout << "Enter your password: ";
    cin >> password;

    infoNewUser newUserInfo;
    newUserInfo.token = token;
    newUserInfo.password = password;
    newUser.push_back(newUserInfo);

    ofstream tokenFile("C:\\DataBaseCpp\\data\\tokens.txt", ios::app);
    ofstream passwordFile("C:\\DataBaseCpp\\data\\passwords.txt", ios::app);

    if (tokenFile.is_open() && passwordFile.is_open()) {
        tokenFile << token << endl;
        passwordFile << password << endl;
        cout << "New user created successfully!" << endl;
    } else {
        cout << "Unable to open files." << endl;
    }

    tokenFile.close();
    passwordFile.close();
}