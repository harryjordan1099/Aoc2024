#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>



std::vector<std::string> readData() 
{
    std::ifstream infile("/Users/harryjordan/Coding/Aoc2024/data/day6/aoc_input_6_test.txt");
    std::vector<std::string>grid;

    for (std::string line; std::getline(infile, line);) {
        grid.push_back(line);
    }

    return grid;
}

struct Coordinate {
    int x, y;

    // Constructor
    Coordinate(int x, int y) : x(x), y(y) {}

    // Comparison operator for using Coordinate in std::set
    bool operator<(const Coordinate& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

class

coord findGuardPosition(std::vector<std::string>& grid) 
{
    int start_x = 0, start_y = 0, direction = 0;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[r].size(); ++c) {
            if (grid[r][c] == '^') {
                start_x = r;
                start_y = c;
                direction = 0; // Up
                break;
            }
        }
    }

}


int main() 
{
    std::vector<std::string> grid = readData();
    return 0;
}
