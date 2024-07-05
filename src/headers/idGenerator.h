#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

std::set<int> generatedIDs;

int generateID() {
    srand(time(NULL));
    int id;
    do {
        id = rand() % 9000000 + 1000000;
    } while (generatedIDs.find(id) != generatedIDs.end());
    generatedIDs.insert(id);
    return id;
}