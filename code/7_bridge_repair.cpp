#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>



std::unordered_map<long, std::vector<int>> readData() 
{
    std::ifstream infile("/Users/harryjordan/Coding/Aoc2024/data/day7/aoc_input_7.txt");
    std::unordered_map<long, std::vector<int>> equations;


    for (std::string line; std::getline(infile, line);) 
    {
        std::istringstream iss(line);

        // getting key
        long key;
        char colon;
        iss >> key >> colon;

        // getting values
        std::vector<int> values;
        int value;
        while (iss >> value) 
        {
            values.push_back(value);
        }
        equations[key] = values;
    }

    infile.close();
    // checking result
    
    // for (const auto& [key, values] : equations) 
    // {
    //     std::cout << key << ": ";
    //     for (int val : values)
    //     {
    //         std::cout << val << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return equations;
}

bool findOperations(std::vector<int>& numbers, const long& target) 
// This function should determine whether an equation can be solved
{

    std::vector< std::unordered_map< int, std::string > > dp(numbers.size());
    dp[0][numbers[0]] = std::to_string(numbers[0]);

    for (int i = 1; i < numbers.size(); ++i)
    {
        int current_num = numbers[i];
        for (const auto& [value, expr] : dp[i - 1]) 
        {
            int new_value_add = value + current_num;
            dp[i][new_value_add] = "(" + expr + " + " + std::to_string(current_num) + ")";

            int new_value_mul = value * current_num;
            dp[i][new_value_mul] = "(" + expr + " * " + std::to_string(current_num) + ")";

        }

    }
    if (dp.back().count(target))
    {
        return true;
    }
    else
    {
        return false;
    }
}

long findTotalCalibration(std::unordered_map<long int,std::vector<int>> equations) 

{
    long total = 0;

    for (auto& [target, numbers] : equations) 
    {
        if (findOperations(numbers, target))
        {
            total = total + target;
        } 
        else 
        {
            continue;
        }
    }
    return total;
}

int main() 
{
    std::unordered_map<long ,std::vector<int>> equations = readData();
    long result = findTotalCalibration(equations);

    std::cout << result << std::endl;

    return 0;

}