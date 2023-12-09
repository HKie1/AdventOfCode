#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>

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
