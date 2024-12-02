#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <tuple> 
#include <unordered_map> 

// Day 1: Historian Hysteria
// Part one:

std::tuple<std::vector<int>, std::vector<int> > readFileInput() {
    
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
        return {};
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

    return {list1, list2};
}

int absoluteDifference(int a, int b) {
    return std::abs(a - b);
}

int calculateDistance() {

    /*
    Pseduo code first
    Input: None
    Output: None (will print output to console)

    Variables:
        int total = 0 (Final output)

    - Sort both lists (Might need to define new lists or sort in place)
    - for i in range(0, len(list1)):
        total += absolute_difference(list1[i], list2[i])
    
    print(total)
    return 0;

    
    
    */

    int total = 0;
    std::vector<int> list1;
    std::vector<int> list2;

    std::tie(list1, list2) = readFileInput();

    std::sort(list1.begin(), list1.end()); 
    std::sort(list2.begin(), list2.end()); 

    for (int i = 0; i < list1.size(); ++i) {
        int diff = absoluteDifference(list1[i], list2[i]);
        total = total + diff;
    }
    std::cout << "Total difference " << total << std::endl;
    return 0; 
}

int calculateSimilarity() {
    /*
    
    - Create hashmap from first list
    - for i in range(0, len(list2)):
        if i is in hashmap:
            increase its value by 1
        else:
            continue
    */
    int similarity_score = 0;
    std::vector<int> list1;
    std::vector<int> list2;

    std::tie(list1, list2) = readFileInput();

    int similarity_total = 0;
    for (int num : list1) {
        int count = 0;
        int similarity = 0;
        for (int num2 : list2) {
            if (num == num2) {
                count++;

            }
            similarity = count * num;

        }
        similarity_total = similarity_total + similarity;


    }

    std::cout << "Similarity score " << similarity_total << std::endl;
    return 0;

}

int main() {
    calculateDistance();
    calculateSimilarity(); 
    return 0;
}

