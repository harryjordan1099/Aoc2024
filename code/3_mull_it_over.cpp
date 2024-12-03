#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <regex>
#include <numeric>

int extractNumbers(const std::string& input) {
    size_t start = input.find('(') + 1; // Find the '(' and move one position forward
    size_t end = input.find(')');       // Find the ')'

    std::string numbers = input.substr(start, end - start);

    std::stringstream ss(numbers);
    int num1, num2;
    char comma;

    // Extract the two integers separated by a comma
    ss >> num1 >> comma >> num2;

    int product = num1 * num2;
    return product;
}

std::string readFileInput() {
    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/input_aoc_3.txt";

    std::ifstream inputFile(filepath);
    if (!inputFile) {
        std::cerr << "Error: File not found at " << filepath << std::endl;
        return ""; // Return an empty string if the file cannot be opened
    }

    // Read the file content into a string
    std::ostringstream buffer;
    buffer << inputFile.rdbuf(); // Read all data from the file into the buffer
    return buffer.str();         // Convert the buffer to a string
}

int main() {
    std::string input = readFileInput();

    std::regex pattern(R"(mul\(\d+,\d+\))");

    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    std::vector<int> matches;

    while (it != end) {
        std::string string_output = it->str();
        int int_output = extractNumbers(string_output);

        matches.push_back(int_output);
        ++it;
        
    }
    int sum_of_elems = std::accumulate(matches.begin(), matches.end(), 0);

    std::cout << sum_of_elems <<std::endl;
    return 0;
}