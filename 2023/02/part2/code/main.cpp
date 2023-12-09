#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

static std::regex_token_iterator<std::string::iterator> iter_end;

uint64_t findMaxOfColor(std::string input, std::string color)
{
    std::vector<uint64_t> values;
    std::string match = "(\\d+) " + color;
    std::regex regex_red(match, std::regex_constants::ECMAScript | std::regex_constants::icase);

    std::regex_token_iterator<std::string::iterator> regex_matches(input.begin(), input.end(), regex_red, 1);
    while (regex_matches != iter_end)
    {
        std::cout << " " << *regex_matches;
        values.push_back(std::stoi(*regex_matches));
        regex_matches++;
    }
    std::cout << std::endl;
    return *std::max_element(values.begin(), values.end());
}

int main()
{
    // open input file
    std::ifstream input;
    input.open("input.txt");
    std::string lineOfFile = "";

    uint64_t final_sum = 0;
    uint64_t gamecount = 1;

    while (getline(input, lineOfFile))
    {
        std::cout << lineOfFile << "\n";

        uint64_t max_red = findMaxOfColor(lineOfFile, "red");
        uint64_t max_green = findMaxOfColor(lineOfFile, "green");
        uint64_t max_blue = findMaxOfColor(lineOfFile, "blue");

        uint64_t setPower = max_red * max_green * max_blue;
        final_sum += setPower;

        ++gamecount;
    }
    
    // close input file
    input.close();

    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
