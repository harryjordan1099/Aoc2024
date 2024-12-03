#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <regex>
#include <numeric>


// This function is used to calculate the product from the regex
int extractNumbers(const std::string& input) {
    // Find the '(' and move one position forward to fidn the first digit
    size_t start = input.find('(') + 1; 
    size_t end = input.find(')');       // Find the ')'

    // Extract the numbers first as a substring
    std::string numbers = input.substr(start, end - start);

    /* 
    string stream allows for extraction of individual values
    whereas idnexing would be a ballache, we can use stringstream to automatically
    parse double digit numbers and such 
    */
    std::stringstream ss(numbers);
    int num1, num2;
    char comma;

    // Extract the two integers separated by a comma
    // ss extracts first integer, then the comma, then the second integer
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

    // Read the file content into a string, you can use ostringstream here as 
    // we are just outputting, vs stringstream which does read a write
    std::stringstream buffer;
    buffer << inputFile.rdbuf(); // Read all data from the file into the buffer
    return buffer.str();         // Convert the buffer to a string
}

int main() {
    std::string input = readFileInput();
    // std::string input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    std::regex pattern(R"regex((mul\(\d+,\d+\))|(do\(\))|(don't\(\)))regex");


    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    std::vector<int> matches;

    bool do_or_dont = true;

    while (it != end) {
        std::smatch match = *it;
        if (match[1].matched && do_or_dont) {
            int int_output = extractNumbers(match[1].str());
            matches.push_back(int_output);
        } else if (match[2].matched) {
            do_or_dont = true;
        } else if (match[3].matched) {
            do_or_dont = false;
        }
        ++it;
        
    }
    int sum_of_elems = std::accumulate(matches.begin(), matches.end(), 0);

    std::cout << sum_of_elems <<std::endl;
    return 0;
}