#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>


std::vector<std::pair<int, int>> readPageOrderingInput() {
    std::vector<std::string> test_input = {
        "47|53",
        "97|13",
        "97|61",
        "97|47",
        "75|29",
        "61|13",
        "75|53",
        "29|13",
        "97|29",
        "53|29",
        "61|53",
        "97|53",
        "61|29",
        "47|13",
        "75|47",
        "97|75",
        "47|61",
        "75|61",
        "47|29",
        "75|13",
        "53|13"
    };

    std::vector<std::pair<int, int>> parsedInput;
    for (const auto& row : test_input) {
        std::stringstream ss(row);
        int num1, num2;
        char delimiter; // To capture the '|'

        // Parse numbers separated by '|'
        if (ss >> num1 >> delimiter >> num2 && delimiter == '|') {
            parsedInput.emplace_back(num1, num2);
        }
    }

    return parsedInput;

}

std::vector<std::vector<int>> readPageUpdateInput() {
    std::vector<std::string> test_input = {
        "75,47,61,53,29",
        "97,61,53,29,13",
        "75,29,13",
        "75,97,47,61,53",
        "61,13,29",
        "97,13,75,29,47"
    };

    std::vector<std::vector<int>> parsed_data;

    for (const auto& row : test_input) {
        std::vector<int> numbers;
        std::stringstream ss(row);
        std::string token;

        while (std::getline(ss, token, ',')) {
            numbers.push_back(std::stoi(token));
        }

        parsed_data.push_back(numbers);
    }

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
