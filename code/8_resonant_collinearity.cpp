#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>


std::vector<std::string> readData() 
{
    std::ifstream infile("/Users/harryjordan/Coding/Aoc2024/data/day8/aoc_input_8.txt");
    std::vector<std::string> grid; 

    for (std::string line; std::getline(infile, line);) 
    {
        std::istringstream iss(line);
        grid.push_back(line);
    }

    return grid;

}

std::unordered_map<char, std::vector<std::pair<int, int>>> findAntennas(std::vector<std::string>& grid) 
{
    std::unordered_map<char, std::vector<std::pair<int, int>>> character_coordinates;
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[0].size(); ++x)
        {
            if (grid[y][x] != '.')
            {
                // Creating/Finding the correct key and assigning a coordinate to it (y, x)
                char key = grid[y][x];
                character_coordinates[key].push_back(std::make_pair(y, x));
            }
        }
    }

    return character_coordinates;
} 

int findTotalAntinodes (std::vector<std::string>& grid)
{

    std::unordered_map<char, std::vector<std::pair<int, int>>> character_coordinates = findAntennas(grid);

    std::set<std::pair<int, int>> antinodes;
    // Iterate through all the characters
    for (const auto& [characters_key, coordinates] : character_coordinates)
    {
        std::cout << characters_key << std::endl;
        // Comparing pairs of coordinates
        for (int i = 0; i < coordinates.size(); ++i)
        {
            for (int j = i + 1; j < coordinates.size(); ++j)
            {
                // Create points a and b of a particular character c
                std::pair<int, int> a = coordinates[i];
                std::pair<int, int> b = coordinates[j];

                // Calculate distance
                int dy = b.first - a.first;
                int dx = b.second - a.second;

                // Create each antinode
                std::pair<int, int> N1 = std::make_pair(a.first - dy, a.second - dx); 
                std::pair<int, int> N2 = std::make_pair(b.first + dy, b.second + dx);

                // Check if they are both in grid and not a duplicate of another anti node
                if (N1.first >= 0 && N1.first < grid.size() && N1.second >= 0 && N1.second < grid[0].size())
                {
                    antinodes.insert(N1);
                    grid[N1.first][N1.second] = '#';
                }


                if (N2.first >= 0 && N2.first < grid.size() && N2.second >= 0 && N2.second < grid[0].size())
                    {
                        antinodes.insert(N2);
                        grid[N2.first][N2.second] = '#';
                    }
            }
        }

        
    }
        // // printing grid
    for (auto const& row: grid)
    {
        std::cout << row << std::endl;
    }
    return antinodes.size();
}

int findTotalAntinodesHarmonics (std::vector<std::string>& grid)
{

    // for (auto const& row: grid)
    // {
    //     std::cout << row << std::endl;
    // }

    std::unordered_map<char, std::vector<std::pair<int, int>>> character_coordinates = findAntennas(grid);

    std::set<std::pair<int, int>> antinodes;
    // Iterate through all the characters
    for (const auto& [characters_key, coordinates] : character_coordinates)
    {
        // Comparing pairs of coordinates
        for (int i = 0; i < coordinates.size(); ++i)
        {
            for (int j = i + 1; j < coordinates.size(); ++j)
            {
                // Create points a and b of a particular character c
                std::pair<int, int> a = coordinates[i];
                std::pair<int, int> b = coordinates[j];

                antinodes.insert(a);
                antinodes.insert(b);

                // Calculate distance
                int dy = b.first - a.first;
                int dx = b.second - a.second;

                // Create each antinode
                std::pair<int, int> N1 = std::make_pair(a.first - dy, a.second - dx); 
                std::pair<int, int> N2 = std::make_pair(b.first + dy, b.second + dx);

                // Check if they are both in grid and not a duplicate of another anti node
                while (N1.first >= 0 && N1.first < grid.size() && N1.second >= 0 && N1.second < grid[0].size())
                {
                    antinodes.insert(N1);

                    if (grid[N1.first][N1.second] == '.')
                        {
                            grid[N1.first][N1.second] = '#';
                        }

                    N1 = std::make_pair(N1.first - dy, N1.second - dx); 
                }


                while (N2.first >= 0 && N2.first < grid.size() && N2.second >= 0 && N2.second < grid[0].size())
                    {
                        antinodes.insert(N2);

                        if (grid[N2.first][N2.second] == '.')
                        {
                            grid[N2.first][N2.second] = '#';
                        }

                        N2 = std::make_pair(N2.first + dy, N2.second + dx); 
                    }
            }
        }

        
    }
        // // printing grid
    for (auto const& row: grid)
    {
        std::cout << row << std::endl;
    }
    return antinodes.size();
}

int main() 
{   
    std::vector<std::string> grid = readData();

    std::unordered_map<char, std::vector<std::pair<int, int>>> coord = findAntennas(grid);
    
    int antinodes = findTotalAntinodesHarmonics(grid);

    std::cout << antinodes << std::endl;

    
    
    return 0;
}