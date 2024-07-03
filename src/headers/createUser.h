bool fileIsEmpty(const std::string& filename) {
    std::ifstream inFile(filename);
    return inFile.peek() == std::ifstream::traits_type::eof();
}

void createUser(const std::string& filename) {
    std::string login, password;

    if (!fileIsEmpty(filename)) {
        std::cout << "Error: User already exists. Only one user can be created." << std::endl;
        return;
    }

    std::cout << "\nEnter new login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    outFile << login << std::endl << password << std::endl;
    outFile.close();

    std::cout << "User created successfully!" << std::endl;
}