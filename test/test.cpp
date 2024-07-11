#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Product {
    string name;
    int ID;
    float price;
};

vector<Product> myDataBase = {
    {"ProductA", 1, 10.0},
    {"ProductB", 2, 20.0},
    {"ProductC", 3, 15.0}
};

enum class SortOption {
    NAME,
    ID,
    PRICE,
    NONE
};

void printData(SortOption sortOption = SortOption::NONE) {
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

int main() {
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
        default:
            break;
    }
    printData(sortOption);

    return 0;
}
