#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>

void sanitizeInput(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        ++start_pos;
    }
}

int main()
{
    // open input file
    std::ifstream input;
    input.open("input.txt");

    std::string lineOfFile = "";
    uint64_t final_sum = 0;

    // read every line of file
    while (!input.eof())
    {
        std::string lineString = "";
        std::vector<std::string> digits;
        input >> lineOfFile;

        std::cout << lineOfFile << std::endl;

        // replace strings with numbers to make the folloing code work
        // replace with beginning and end respectivel to make overlapping numbers work
        sanitizeInput(lineOfFile, "one", "on1ne");
        sanitizeInput(lineOfFile, "two", "tw2wo");
        sanitizeInput(lineOfFile, "three", "thre3hree");
        sanitizeInput(lineOfFile, "four", "fou4our");
        sanitizeInput(lineOfFile, "five", "fiv5ive");
        sanitizeInput(lineOfFile, "six", "si6ix");
        sanitizeInput(lineOfFile, "seven", "seve7even");
        sanitizeInput(lineOfFile, "eight", "eigh8ight");
        sanitizeInput(lineOfFile, "nine", "nin9ine");

        // iterate over every character and check if character is a digit - first digit
        for(std::string::iterator c = lineOfFile.begin(); c != lineOfFile.end(); ++c)
        {
            if (isdigit(*c))
            {
                digits.push_back(std::string()+*c);
                break;
            }
        }

        reverse(lineOfFile.begin(), lineOfFile.end());

        // iterate over every character and check if character is a digit - first digit
        for(std::string::iterator c = lineOfFile.begin(); c != lineOfFile.end(); ++c)
        {
            if (isdigit(*c))
            {
                digits.push_back(std::string()+*c);
                break;
            }
        }

        // read and pop front elemets
        lineString += digits.front();
        digits.erase(digits.begin());
        lineString += digits.front();
        digits.erase(digits.begin());

        std::cout << "--> " << lineString << " + " << final_sum << std::endl;

        // cast line result to integer type and add to final sum
        uint64_t final_line = std::stoi(lineString.c_str());
        final_sum += final_line;
        
    }
    
    // close input file
    input.close();

    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
