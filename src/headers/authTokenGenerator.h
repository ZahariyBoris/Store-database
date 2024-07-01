#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

string generateAuthToken(int length = 32) {
    srand(time(NULL));

    if (length <= 0) {
        throw runtime_error("Length must be a positive integer");
    }

    string token = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; ++i) {
        token += alphanum[rand() % (sizeof(alphanum))];
    }

    return token;
}