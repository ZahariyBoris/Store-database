#include <iostream>
#include <cstdlib>
#include <ctime>

int generateID() {
    srand(time(NULL));
    return rand() % 9000000 + 1000000;
}