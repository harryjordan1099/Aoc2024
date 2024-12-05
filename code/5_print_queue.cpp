#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>


std::vector<std::pair<int, int>> readPageOrderingInput() {
    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/input_aoc5_order.txt";
    
    std::ifstream inputFile(filepath);

    if (!inputFile) {
        std::cerr << "File not found! " << std::endl;
        return {};
    }

    std::vector<std::pair<int, int>> parsedInput;
    std::string line;
    
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string first_str, second_str;

        // Split the line into two parts at the '|'
        if (std::getline(ss, first_str, '|') && std::getline(ss, second_str)) {
            // Convert the strings to integers
            int first = std::stoi(first_str);
            int second = std::stoi(second_str);
            
            // Add the pair to the vector
            parsedInput.push_back(std::make_pair(first, second));
        }
    }

    inputFile.close();

    return parsedInput;

}

std::vector<std::vector<int>> readPageUpdateInput() {
    std::string filepath = "/Users/harryjordan/Coding/Aoc2024/data/input_aoc5_update.txt";
    
    std::ifstream inputFile(filepath);

    if (!inputFile) {
        std::cerr << "File not found! " << std::endl;
        return {};
    }

    std::vector<std::vector<int>> parsed_data;

    std::string line;
    
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string number_str;
        std::vector<int> row;
        
        // Split the line by commas and convert to integers
        while (std::getline(ss, number_str, ',')) {
            row.push_back(std::stoi(number_str)); // Convert string to integer and add to the row
        }

        // Add the row to the data vector
        parsed_data.push_back(row);
    }

    inputFile.close();

    return parsed_data;
}

bool checkOrdering(int& before, int& after, std::vector<int>& pagelist) {
    // Find indices of before and after
    // If either valuesd arent present, we will just return true
    // check if index before < after
    int before_index = 0;
    int after_index = 1;
    auto before_it = std::find(pagelist.begin(), pagelist.end(), before);
    if (before_it != pagelist.end()) {
        before_index = std::distance(pagelist.begin(), before_it); // before index
        // std::cout << before_index <<std::endl;
    } else {
        return true; // Cant find before index, then rule invalid, pass as true
    }

    auto after_it = std::find(pagelist.begin(), pagelist.end(), after);
    if (after_it != pagelist.end()) {
        after_index = std::distance(pagelist.begin(), after_it); // after index
        // std::cout << after_index << std::endl;
    } else {
        return true; // Cant find after index, then rule invalid, pass as true
    }
        
    return before_index < after_index;

}

int findMiddle(std::vector<int>& ordered_row) {
    int middle_index = ordered_row.size() / 2;
    return ordered_row[middle_index];
}




int main() {
    std::vector<std::pair<int, int>> ordering = readPageOrderingInput();
    std::vector<std::vector<int>> pageupdate = readPageUpdateInput(); 

    std::vector<int> middle_values;
    for (std::vector<int>& row : pageupdate) {
        bool all_pairs_pass = true;
        for (std::pair<int, int>& pair : ordering) {
            if (!checkOrdering(pair.first, pair.second, row)) {
                all_pairs_pass=false;
                break;
            }

        }
        if (all_pairs_pass) {
            std::cout << findMiddle(row) << std::endl;
            middle_values.push_back(findMiddle(row));
        }

    }
    int sum_of_elems = std::accumulate(middle_values.begin(), middle_values.end(), 0);

    std::cout << sum_of_elems << std::endl;
    return sum_of_elems;
}

// int main() {
//     std::vector<std::pair<int, int>> ordering = readPageOrderingInput();
//     std::vector<std::vector<int>> pageupdate = readPageUpdateInput(); 

//     std::pair<int, int> test = {97, 75};
//     std::vector<int> page_update = pageupdate[3];

//     bool outcome = checkOrdering(test.first, test.second, page_update);

//     std::cout << outcome << std::endl;
    
//     // for (int num : page_update) {
//     //     std::cout << num << " ";
//     //     }
//     //     std::cout << "\n";
// }
