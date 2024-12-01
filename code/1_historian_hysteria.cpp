#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

// Day 1: Historian Hysteria

int readFileInput() {
    
    // Input file path
    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/aoc_input_1.txt";

    // store two lists
    std::vector<int> list1;
    std::vector<int> list2;

    // ifstream is used for reading in files
    std::ifstream inputFile(filepath);

    // check if file was read
    if (!inputFile) {
        std::cerr << "Error: Could not open the file " << filepath << std::endl;
        return 1;
    }

    // Read the file line by line
    // Create line string variable
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int num1, num2;

        // Reading the numbers from the line via inference
        if (iss >> num1 >> num2) {
            list1.push_back(num1);
            list2.push_back(num2);
        }

    }

    inputFile.close();

    // Display the lists

    std::cout << "First 5 values of List 1:" << std::endl;
    for (int i = 0; i < 5 && i < list1.size(); ++i) {
        std::cout << list1[i] << " ";
    }
    std::cout << std::endl;

        std::cout << "First 5 values of List 2" << std::endl;
    for (int i = 0; i < 5 && i < list2.size(); ++i) {
        std::cout << list2[i] << " ";
    }

    std::cout << std::endl;
    
    return 0;
}

