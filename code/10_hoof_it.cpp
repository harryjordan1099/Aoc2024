#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>

/* 
0. load input - Done
1. Find all trailheads
2. Recursively find all the trails that reach 9 by incremeting by 1 from a trail head
3. Count those paths for that trail head.
4. Do this for all trail heads and add them together
*/

std::vector<std::vector<int > > readData()
{       
    // Input 
    std::string input_path = "/Users/harryjordan/Coding/Aoc2024/data/day10/aoc_input_10.txt";
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

std::vector<std::pair<int, int>> findPoints(std::vector<std::vector<int > >& grid, int point)
{

    // Output
    std::vector<std::pair<int, int>> trail_point_indices;

    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == point)
            {
                trail_point_indices.push_back(std::make_pair(i, j));
            }
        }
    }

    return trail_point_indices;
}
std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int number_of_trails;

void traverse(int i, int j, std::vector<int> path, std::set<std::pair<int, int>>& unique_endpoints, const std::vector<std::vector<int > >& grid)
    {
        // Add current postion
        path.push_back(grid[i][j]);

        // Print for debugging
        for (auto i: path)
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';

        // Check if end has been found
        if (grid[i][j] == 9 && unique_endpoints.find(std::make_pair(i, j)) == unique_endpoints.end())
        {
            std::cout << "Valid path found!" << std::endl;
            ++number_of_trails;
            // unique_endpoints.insert(std::make_pair(i, j));
            return;
        }

        // Check all direction
        for (auto& pair: directions)
        {
            int ni = i + pair.first;
            int nj = j + pair.second;

            if (0 <= ni && ni < grid.size() && 0 <= nj && nj < grid[0].size() &&
                std::find(path.begin(), path.end(), grid[ni][nj]) == path.end() &&
                grid[ni][nj] == grid[i][j] + 1)
            {
                traverse(ni, nj, path, unique_endpoints, grid);
            }

        }

    }
        

int findGoodTrails(std::vector<std::pair<int, int>> & trail_head_indices, std::vector<std::vector<int > >& grid)
{
    number_of_trails = 0;
    for (auto& pair: trail_head_indices)
    {
        std::vector<int> path;
        std::set<std::pair<int, int>> unique_endpoints;
        traverse(pair.first, pair.second, path, unique_endpoints, grid);
    }

    return number_of_trails;
}



int main()
{
    auto grid = readData();
    // for (int i = 0; i < grid.size(); ++i)
    // {
    //     for (int j = 0; j < grid[0].size(); ++j)
    //     {
    //         std::cout << grid[i][j] << " "; 
    //     }
    //     std::cout << "\n";
    // }
    auto trail_heads = findPoints(grid, 0);
    // for (const auto& pair: trail_heads)
    // {
    //     std::cout << pair.first << " " << pair.second << std::endl;
    // }
    int number_of_trails = findGoodTrails(trail_heads, grid);
    std::cout << "Number of good trails: " << number_of_trails << std::endl;
    // empty path
    return 0;
}