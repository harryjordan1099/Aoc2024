#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>



std::vector<std::string> readData()
{
    std::ifstream infile("../data/day12/aoc_input_12_test_1.txt");
    std::vector<std::string> garden; 

    for (std::string line; std::getline(infile, line);) 
    {
        std::istringstream iss(line);
        garden.push_back(line);
    }

    return garden;
}

std::set<char> findAllUniqueCharacters(std::vector<std::string>& garden)
{
    std::set<char> unique_characters;

    for (std::string& row: garden)
    {
        for (char& c: row)
        {
            if (unique_characters.find(c) == unique_characters.end())
            {
                unique_characters.insert(c);
            }
        }
    }

    return unique_characters;

}
int numOfNeighbours(std::vector<std::string>& garden, int i, int j, char c)
{
    int count = 0;
 
    // UP
    if (i > 0 && garden[i - 1][j] == c)
        count++;
 
    // LEFT
    if (j > 0 && garden[i][j - 1] == c)
        count++;
 
    // DOWN
    if (i < garden.size() - 1 && garden[i + 1][j] == c)
        count++;
 
    // RIGHT
    if (j < garden[0].size() - 1 && garden[i][j + 1] == c)
        count++;
 
    return count;
}

int findPerimeter(char c, std::vector<std::string>& garden)
{
    int perimeter = 0;

    for (int i = 0; i < garden.size(); ++i)
    {
        for (int j = 0; j < garden[0].size(); ++j)
        {
            if (garden[i][j] == c)
            {
                perimeter += 4 - numOfNeighbours(garden, i, j, c);
            }
        }
    }

    return perimeter;
}

void area_dfs(std::vector<std::string>& grid, std::vector<std::vector<bool> >& visited, int i, int j, int& area)
{
    int rows = grid.size();
    int cols = grid[0].size();

    // check if out of bounds
    if (i < 0 || i >= rows || j < 0 || j >= cols || visited[i][j] || grid[i][j])
    {
        return;
    }

    // Finding area
    area++;

    // Explore neighbors (4-connected)
    area_dfs(grid, visited, i - 1, j, area); // Up
    area_dfs(grid, visited, i + 1, j, area); // Down
    area_dfs(grid, visited, i, j - 1, area); // Left
    area_dfs(grid, visited, i, j + 1, area); // Right


}

std::vector<int> findAreas(char c, std::vector<std::string>& grid)
{
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    std::vector<int> areas;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == c && !visited[i][j])
            {
                int area = 0;
                area_dfs(grid, visited, i, j, area);
                areas.push_back(area);
            }
        }
    }

    return areas;

}



long findCost(std::set<char>& unique_characters, std::vector<std::string>& garden)
{
    /*
    for each letter
    - find perimeter
    - find area
    - mulitply the totals

    */

   int total_cost = 0;

   for (auto c: unique_characters)
   {
    int perimeter = findPerimeter(c, garden);
    std::vector<int> areas = findAreas(c, garden);

    for (auto& area : areas)
    {
        std::cout << area << std::endl;
    }


    int total_cost = std::accumulate(areas.begin(), areas.end(), 0, [&](int acc, int x) 
        {
        return acc + x * perimeter;
        });
   }

   return total_cost;
}

int main() 
{
    std::vector<std::string> garden = readData();

    std::set<char> unique_characters = findAllUniqueCharacters(garden);
    int output = findCost(unique_characters , garden);
    std::cout << "Cost: " << output << std::endl;

    return 0;

}