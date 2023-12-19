#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <bits/stdc++.h>

std::vector<std::pair<uint64_t, std::string>> findDigitPositions(std::string input)
{
    std::vector<std::pair<uint64_t, std::string>> values;
    std::regex regex("\\d+");
    std::smatch match;
    uint64_t lastFound = 0;
    while (std::regex_search(input, match, regex))
    {
        values.push_back(std::make_pair<uint64_t, std::string>(lastFound + match.position(0), match.str()));
        lastFound = lastFound + match.position(0) + match.length();
        input = match.suffix().str();
    }
    return values;
}

int main()
{
    // open input file
    std::ifstream input;
    input.open("input.txt");
    std::string lineOfFile = "";
    std::vector<std::string> fileLines;
    std::vector<std::pair<uint64_t, std::string>> allDigits;

    uint64_t final_sum = 0;

    // fill vector with all lines
    while (getline(input, lineOfFile))
    {
        fileLines.push_back(lineOfFile);
    }

    // iterate all lines
    for (auto lineOfFile = begin(fileLines); lineOfFile != end(fileLines); lineOfFile++)
    {
        // look for digits in this line
        auto res = findDigitPositions(*lineOfFile);

        // find surrounding of this digit
        for (auto &result : res)
        {
            int64_t pos = result.first;
            std::string number = result.second;

            // get line before the current one with width of the match +-1
            std::string before = *(lineOfFile - 1);
            before = before.substr(pos - 1, number.size() + 2);
            std::cout << before << std::endl;

            // get the current line  with width of the match +-1
            std::string inLine = *(lineOfFile);
            inLine = inLine.substr(pos - 1, number.size() + 2);
            std::cout << inLine << std::endl;

            // get line after the current one with width of the match +-1
            std::string after = *(lineOfFile + 1);
            after = after.substr(pos - 1, number.size() + 2);
            std::cout << after << "\n"
                      << std::endl;

            // regex to match all symbols
            const std::regex symbolpattern("[^\\.|^\\d]");
            auto allStrings = before + inLine + after;

            // count matches
            const std::ptrdiff_t match_count(std::distance(
                std::sregex_iterator(allStrings.begin(), allStrings.end(), symbolpattern),
                std::sregex_iterator()));

            // add to sum if there is a symbol nearby
            if (match_count > 0)
            {
                final_sum += std::stoi(number);
            }
        }
    }

    // close input file
    input.close();

    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
