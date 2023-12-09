#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

int main()
{
    // open input file
    std::ifstream input;
    input.open("input.txt");
    std::string lineOfFile = "";


    uint64_t final_sum = 0;

    while (getline(input, lineOfFile))
    {
        std::cout << "LINE:" << lineOfFile << std::endl;

        uint64_t roundpoints = 0;
        std::vector<uint64_t> winning_nums;
        std::regex winningRegex("Card\\s+\\d+:\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+");  
        std::smatch matchesWinning;
        if (std::regex_search(lineOfFile, matchesWinning, winningRegex)) {
            for (uint64_t i = 1; i < matchesWinning.size(); i++)
            {
                winning_nums.emplace_back(std::stoi(matchesWinning[i]));
            }
        }

        std::regex numbersRegex("\\|\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");  
        std::smatch matchesNumbers;
        if (std::regex_search(lineOfFile, matchesNumbers, numbersRegex)) {
            for (uint64_t i = 1; i < matchesNumbers.size(); i++)
            {
                if (std::find(winning_nums.begin(), winning_nums.end(), std::stoi(matchesNumbers[i])) != winning_nums.end())
                {
                    if(0 == roundpoints)
                    {
                        ++roundpoints;
                    }
                    else
                    {
                        roundpoints += roundpoints;
                    }
                }
            }
        }
        std::cout << "Card is worth " << roundpoints << std::endl;
        final_sum += roundpoints;
    }
    
    // close input file
    input.close();

    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
