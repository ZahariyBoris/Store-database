#include <iostream>
#include <fstream>
#include <string>
#include <limits>

bool fileIsEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

void createUser(const std::string& filename) {
    while (true) {
        std::string login;
        int password;

        if (!fileIsEmpty(filename)) {
            std::cout << "Error: User already exists. Only one user can be created." << std::endl;
            return;
        }

        std::cout << "\nEnter new login: ";
        std::cin >> login;

        if (login.empty()) {
            std::cout << "Error: Login cannot be empty. Try again!" << std::endl;
            continue;
        }

        std::cout << "Enter password (must be an integer): ";
        if (!(std::cin >> password) || std::cin.peek() != '\n') {
            std::cout << "Invalid input. Password must be an integer. Please try again!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::ofstream outFile(filename);
        if (!outFile) {
            std::cout << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        outFile << login << std::endl << password << std::endl;
        outFile.close();

        std::cout << "User created successfully!" << std::endl;
        break;
    }
}
