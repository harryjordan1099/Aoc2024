#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/* 
0. load input
1. Find all trailheads
2. Recursively find all the trails that reach 9 by incremeting by 1 from a trail head
3. Count those paths for that trail head.
4. Do this for all trail heads and add them together
*/

std::vector<std::vector<int > > readData()
{       
    // Input 
    std::string input_path = "/Users/harryjordan/Coding/Aoc2024/data/day10/aoc_input_10_test_1.txt";
    std::ifstream inputFile(input_path);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + input_path);
    }

    // Output
    std::vector<std::vector<int > > grid;

    std::vector<int> row;
    std::string line;

    while (std::getline(inputFile, line))
    {
        row.clear();
        for (char ch : line) 
        {
            if (std::isdigit(ch))
            {
                // convert to int
                row.push_back(ch - '0');
            }
            else
            {
                row.push_back(-1);
            }
        }
        grid.push_back(row);
    } 

    return grid;
}

int main()
{
    auto grid = readData();
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            std::cout << grid[i][j] << " "; 
        }
        std::cout << "\n";
    }
    return 0;
}