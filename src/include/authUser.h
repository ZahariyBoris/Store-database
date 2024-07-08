bool authenticateUser(const std::string& filename, const std::string& login, const std::string& password) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == login) {
            std::string storedPassword;
            std::getline(inFile, storedPassword);
            if (storedPassword == password) {
                return true;
            } else {
                return false;
            }
        }
        
        std::getline(inFile, line);
    }
    return false;
}