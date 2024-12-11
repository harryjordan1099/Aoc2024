#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <regex>
#include <numeric>


std::vector<long> readData() 
{   
    std::string file_path = "/Users/harryjordan/Coding/Aoc2024/data/day9/aoc_input_9.txt";

    std::ifstream inputFile(file_path);
    std::vector<long> result;

    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + file_path);
    }

    std::string line;
    while (std::getline(inputFile, line)) 
        { 
        // Read the file line by line
        for (char ch : line) 
            {
            if (std::isdigit(ch)) 
            {
                result.push_back(ch - '0'); // Convert char to integer and add to vector
            } 
            else 
            {
                throw std::invalid_argument("File contains non-digit characters.");
            }
        }
    }

    return result;
}

std::vector<long> expandList(std::vector<long>& inputList)
{
    std::vector<long> expandedList;
    long index = 0;
    for (int i = 0; i < inputList.size(); ++i)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < inputList[i]; ++j)
            {
                expandedList.push_back(index);
            }
            index += 1;
        }
        else
        {
            for (int j = 0; j < inputList[i]; ++j)
            {
                expandedList.push_back(-1);
            }
        }
        
    }

    return expandedList;
}

std::vector<long> compressList(const std::vector<long>& inputList)
{
    std::vector<long> compressed = inputList;

    // Create two lists for empty and filled indices
    std::vector<long> empties, filled;
    for (size_t i = 0; i < inputList.size(); ++i)
    {
        if (inputList[i] < 0) 
        {
            empties.push_back(i);
        }
        else
        {
            filled.push_back(i);
        }
    }

    // Fill the empty slots with values from the filled list
    size_t j = 0;
    for (auto it = filled.rbegin(); it != filled.rend() && j < empties.size(); ++it)
    {
        if (*it < empties[j])
        {
            break; // Stop if the filled index is less than the current empty index
        }
        compressed[empties[j]] = inputList[*it];
        compressed[*it] = -1;
        ++j;
    }

    return compressed;
}

long checkSum(std::vector<long>& inputList)
{
    long sum = 0;
    for (int i = 0; i < inputList.size(); ++i)
    {
        if (inputList[i] >= 0)
        {
            sum += i * inputList[i];
        }
    }
    return sum;
}

int main() 
{   

    std::vector<long> input_string = readData();
    std::vector<long> expandedList = expandList(input_string);
    std::cout << "Expanded list: " << std::endl;
    // for (int i : expandedList)
    // {
    //     std::cout << i << " ";
    // }
    std::cout << "\n" << std::endl;
    std::vector<long> compressedList = compressList(expandedList);
    std::cout << "Compressed list: " << std::endl;
    // for (int i : compressedList)
    // {
    //     std::cout << i << " ";
    // }
    long checksum = checkSum(compressedList); 
    std::cout << checksum << std::endl;
    return 0;
}