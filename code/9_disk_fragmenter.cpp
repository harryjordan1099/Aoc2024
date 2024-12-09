#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <regex>
#include <numeric>


std::vector<int> readData() 
{   
    std::string file_path = "/Users/harryjordan/Coding/Aoc2024/data/day9/aoc_input_9_test.txt";

    std::ifstream inputFile(file_path);
    std::vector<int> result;

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

std::vector<int> expandList(std::vector<int>& inputList)
{
    std::vector<int> expandedList;
    int index = 0;
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
        else if (i % 2 == 1)
        {
            for (int j = 0; j < inputList[i]; ++j)
            {
                expandedList.push_back(-1);
            }
        }
        
    }

    return expandedList;
}

std::vector<int> compressList(std::vector<int>& inputList)
{   
    std::vector<int> emptyIndices;
    std::vector<int> realValues;

    for (int i = 0; i < inputList.size(); ++i)
    {
        if (inputList[i] == -1)
        {
            emptyIndices.push_back(i);
        }
        else
        {
            realValues.push_back(inputList[i]);
        }
    }
    std::cout<< realValues.back() << std::endl;

    for (int j = 0; j < inputList.size(); ++j)
    {

         if (inputList[j] == -1)
         {
            inputList[j] = realValues.back();
            realValues.pop_back();
         } else {
            continue;
         }
    }

    return inputList;
}

int checkSum(std::vector<int>& inputList)
{
    int sum = 0;
    for (int i = 0; i < inputList.size(); ++i)
    {
        sum += i * inputList[i];
    }
    return sum;
}

int main() 
{   
    std::vector<int> input_string = readData();
    std::vector<int> expandedList = expandList(input_string);
    for (int i : expandedList)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::vector<int> compressedList = compressList(expandedList);
    for (int i : compressedList)
    {
        std::cout << i << " ";
    }

    int checksum = checkSum(compressedList); 
    std::cout << checksum << std::endl;
    return 0;
}