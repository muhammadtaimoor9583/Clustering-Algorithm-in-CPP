#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream inputFile("dataSet.txt"); // Replace "your_file.txt" with your file name
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string col1, col2;
        double col3;

        if (iss >> col1 >> col2 >> col3) {
            // Process the read data (for example, print them)
            std::cout << "Column 1: " << col1 << "\tColumn 2: " << col2 << "\tColumn 3: " << col3 << std::endl;
        } else {
            std::cerr << "Error reading line!" << std::endl;
        }
    }

    inputFile.close();
    return 0;
}
