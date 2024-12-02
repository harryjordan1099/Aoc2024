#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>


std::vector<std::vector<int> > readFileInput() {
    // Input file path

    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/aoc2_input.txt";
    
    std::ifstream inputFile(filepath);

    if (!inputFile) {
        std::cerr << "File not found! " << std::endl;
        return {};
    }

    // defining variables
    std::vector<std::vector<int> > raggedArray;
    std::string line;

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        int number;
        std::vector<int> row;
        std::istringstream iss(line);

        // Extract the numbers from each row
        while (iss >> number) {
            row.push_back(number);
        }

        raggedArray.push_back(row);
        
    }

    inputFile.close();

    // Display part of array

    std::cout << "First 5 rows of input" << std::endl;
    for (size_t i = 0; i < 5 && i < raggedArray.size(); ++i) {
        for (const auto& num : raggedArray[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return raggedArray;
}

int getSign(int num) {
    if (num > 0) return 1; 
    if (num < 0) return -1;
    return 0;
}

int calculateSafeReports() {
    std::vector<std::vector<int> > input = readFileInput();

    int number_of_safe_report = 0;

    for (size_t i = 0; i < input.size(); ++i) {

        const auto& row = input[i];
        int correct_sign = getSign(row[1] - row[0]);
        bool is_safe = true;

        for (size_t j = 0; j < row.size() - 1; ++j) {
            int diff = row[i+1] - row[i];

            if ((diff > 3) || (diff < 1) || (getSign(diff) != correct_sign)) {
                is_safe = false;
                break;
                }

        }
        if (is_safe) {
            number_of_safe_report++;
            }

        
    }
    return number_of_safe_report;
}

int main() {
    int result = calculateSafeReports();
    std::cout << "Number of safe reports: " << result << std::endl;
    return 0;
}
