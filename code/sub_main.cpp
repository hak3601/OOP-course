// File: read_csv.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // Open the file
    std::ifstream file("data/Artificial_intelligence-TF-train.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) { // Read each line
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string value;

        // Split by comma
        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }

        // Print the values in the row (optional)
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // Close the file
    file.close();

    return 0;
}
