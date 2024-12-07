#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>

std::vector<std::string> readData() 
{
    std::ifstream infile("/Users/harryjordan/Coding/Aoc2024/data/day6/aoc_input_6.txt");
    std::vector<std::string> grid;

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

class Guard 
{
    private:
        int x, y;
        int direction;
        bool out_of_bounds; // Track if the guard is out of bounds
        const std::vector<std::string>& grid;
        std::set<Coordinate> visited;

        // Directions (up, right, down, left)
        const std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    public:
        // Constructor
        Guard(int start_x, int start_y, int start_direction, const std::vector<std::string>& grid)
        : x(start_x), y(start_y), direction(start_direction), out_of_bounds(false), grid(grid) 
        {
            visited.insert(Coordinate(x, y));
        }

        bool move() 
        {
            // Update row (vertical position)
            int next_x = x + directions[direction].first;  
            // Update column (horizontal position)
            int next_y = y + directions[direction].second; 

            // Check if the guard is out of bounds
            if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) 
            {
                out_of_bounds = true; // Mark guard as out of bounds
                return false;
            }

            // Check if the next position is not an obstacle
            if (grid[next_x][next_y] != '#') 
            {
                x = next_x;
                y = next_y;
                visited.insert(Coordinate(x, y));
                return true; // Move successful
            }

            return false; // Blocked by obstacle
        }

        void turnRight() 
        {
            direction = (direction + 1) % 4;
        }

        void patrol() 
        {
            while (!out_of_bounds) // Stop patrolling if the guard goes out of bounds
            {
                if (!move()) 
                {
                    turnRight();
                }
            }
        }

        int getVisitedCount() const 
        {
            return visited.size();
        }
};

int main() 
{
    std::vector<std::string> grid = readData();

    int start_x = 0, start_y = 0, start_direction = 0;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[r].size(); ++c) {
            if (grid[r][c] == '^') {
                start_x = r;
                start_y = c;
                start_direction = 0; // Up
                break;
            }
        }
    }

    Guard guard(start_x, start_y, start_direction, grid);
    guard.patrol();

    std::cout << "Unique positions visited: " << guard.getVisitedCount() << std::endl;

    return 0;
}
