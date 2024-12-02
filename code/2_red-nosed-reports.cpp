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

bool isRowSafe(const std::vector<int>& row) {

    int correct_sign = getSign(row[1] - row[0]);

    for (size_t i = 0; i < row.size() - 1; ++i) {
        int diff = row[i+1] - row[i];
        if (std::abs(diff) < 1 || std::abs(diff) > 3 || getSign(diff) != correct_sign || getSign(diff) == 0) { 
            return false;
        }
    }
    return true;
}

int calculateSafeReports() {
    std::vector<std::vector<int> > input = readFileInput();

    int number_of_safe_report = 0;
    std::cout << "Input size: " << input.size() << std::endl;
    for (size_t i = 0; i < input.size(); ++i) {

        const auto& row = input[i];
        int correct_sign = getSign(row[1] - row[0]);
        bool is_safe = true;

        for (size_t j = 0; j < row.size() - 1; ++j) {

            int diff = row[j+1] - row[j];

            if (std::abs(diff) < 1 || std::abs(diff) > 3 || getSign(diff) != correct_sign || getSign(diff) == 0) {
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

int calculateSafeReportsDampener() {
    std::vector<std::vector<int> > input = readFileInput();
    // std::vector<std::vector<int> > input = {
    // {7, 6, 4, 2, 1},      
    // {1, 2, 7, 8, 9},   
    // {9, 7, 6, 2, 1},    
    // {1, 3, 2, 4, 5},        
    // {8, 6, 4, 4, 1},
    // {1, 3, 6, 7, 9},           
    // };

    int number_of_safe_report = 0;
    for (const std::vector<int>& row : input) {

        if (isRowSafe(row)) {
            number_of_safe_report++;
            continue;
        }

    

        bool is_safe_with_drop = false;
        for (size_t i = 0; i < row.size(); ++i) {
            std::vector<int> adjusted_row = row;
            adjusted_row.erase(adjusted_row.begin() + i);

            if (isRowSafe(adjusted_row)) {
                is_safe_with_drop = true;
                break;
            }
        }
        if (is_safe_with_drop) {
            number_of_safe_report++;
        }
    }
    return number_of_safe_report;
}
int main() {
    int sf = calculateSafeReports();
    int sf_dampening = calculateSafeReportsDampener();
    std::cout << "Number of safe reports: " << sf << std::endl;
    std::cout << "Number of safe reports w/ dampening: " << sf_dampening << std::endl;
    return 0;
}
