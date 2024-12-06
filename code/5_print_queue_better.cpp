#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <utility>

struct print_rule {
    int page1{ 0 };
    int page2{ 0 };
};
std::tuple<std::vector<print_rule>, std::vector<std::vector<int>>> read_file()
{
    std::ifstream infile("/Users/harryjordan/Coding/Aoc2024/data/aoc_input_5.txt");
    std::vector<print_rule> rule_rows;
    std::vector<std::vector<int>> csv_rows;

    for (std::string line; std::getline(infile, line);) {

        if (line.empty())
            break;
    
        std::istringstream ss(line);

        int page1{ 0 };
        char vert_line{ 0 };
        int page2{ 0 };
        ss >> page1 >> vert_line >> page2;
        print_rule rule_entry{ page1, page2 };

        rule_rows.push_back(rule_entry);
    }

    for (std::string line; std::getline(infile, line);) {
        std::istringstream ss(line);
        std::vector<int> row;

        int value{ 0 };
        char comma{ 0 };
        while (ss >> value) {
            row.push_back(value);
            if (!(ss >> comma))
                break;
        }

        csv_rows.push_back(std::move(row));

    }

    return { rule_rows, csv_rows };
}

bool is_update_valid(const std::vector<int> &update, const std::vector<print_rule> &rule_list)
{
    auto compare_method = [&rule_list = std::as_const(rule_list)](int a, int b) {
        for (const auto &rule : rule_list) {
            if (rule.page2 == a && rule.page1 == b)
                return false;
        }
        return true;
    };

    return std::is_sorted(update.begin(), update.end(), compare_method);
}

void repair_update(std::vector<int> &update, const std::vector<print_rule> &rule_list)
{
    auto compare_method = [&rule_list = std::as_const(rule_list)](int a, int b) {
        //need to get the relationship between a and b
        //this doesn't handle transitive rules!
        //but thats apparently not required with the ruleset
        for (const auto &rule : rule_list) {
            if (rule.page2 == a && rule.page1 == b)
                return false;
        }
        return true;
    };

    std::sort(update.begin(), update.end(), compare_method);
}

int main()
{
    auto [rule_list, update_list] = read_file();

    int valid_sum{ 0 };
    int repair_sum{ 0 };
    for (auto &update : update_list) {
        //bool is_valid = is_update_valid(update, rule_list);
        bool is_valid = is_update_valid(update, rule_list);

        if (is_valid) {
            size_t middle_index = update.size() / 2;

            valid_sum += update.at(middle_index);
        } else {
            //repair_update(update, rule_list);
            repair_update(update, rule_list);

            size_t middle_index = update.size() / 2;
            repair_sum += update.at(middle_index);
        }
    }

    std::cout << valid_sum << '\n';
    std::cout << repair_sum << '\n';
}





