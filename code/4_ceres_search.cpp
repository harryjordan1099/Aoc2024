#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <tuple> 
#include <unordered_map> 

std::vector<std::string > readFileInput() {

    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/input_aoc_4.txt";
    
    std::ifstream inputFile(filepath);

    if (!inputFile) {
        std::cerr << "File not found! " << std::endl;
        return {};
    }

    std::vector<std::string > wordsearch; 
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    std::istringstream iss(fileContent);
    std::string word;
    while (iss >> word) {
        wordsearch.push_back(word);
    }

    return wordsearch;
} 

int countOccurrences (const std::string& str, const std::string& word) {
    int count = 0;
    size_t pos = str.find(word);

    while (pos != std::string::npos) {
        count++;
        pos = str.find(word, pos + 1);
    }

    return count;
}



int findWords(std::vector<std::string >& wordsearch) {

    // Create left right string, up down string, left right diagonal string, right left diagonal string
    // count the number of times XMAS and SAMX appear in them
    // Output the total amount of times they appear

    int totalOccurrences = 0;
    std::string target1 = "XMAS";
    std::string target2 = "SAMX";

    // Horizontal check
    for (const std::string& row : wordsearch) {
        totalOccurrences += countOccurrences(row, target1);
        totalOccurrences += countOccurrences(row, target2);
    } 
    int numRows = wordsearch.size();
    int numCols = wordsearch[0].size();

    // Vertical check
    for (int col = 0; col < numCols; ++col) {
        std::string column;
        for (int row = 0; row < numRows; ++row) {
            column += wordsearch[row][col];
        }
    // Diagonals
    

    totalOccurrences += countOccurrences(column, target1);
    totalOccurrences += countOccurrences(column, target2);
    }
    for (int start = 0; start < numRows + numCols - 1; ++start) {
        std::string diagonal1, diagonal2;
        for (int row = 0; row < numRows; ++row) {
            int col1 = start - row;
            int col2 = numCols - 1 - (start - row);

            if (col1 >= 0 && col1 < numCols) {
                diagonal1 += wordsearch[row][col1];
            }
            if (col2 >= 0 && col2 < numCols) {
                diagonal2 += wordsearch[row][col2];
            }
        }
        totalOccurrences += countOccurrences(diagonal1, target1);
        totalOccurrences += countOccurrences(diagonal1, target2);

        totalOccurrences += countOccurrences(diagonal2, target1);
        totalOccurrences += countOccurrences(diagonal2, target2);
    }
    return totalOccurrences;
}

int main() {
    std::vector<std::string > wordsearch = readFileInput();
    int totalOccurrences = findWords(wordsearch);
    std::cout << totalOccurrences <<std::endl;
    return 0;
}