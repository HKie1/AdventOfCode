#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <regex>

// define one card
struct cardStruct
{
    // card id
    uint64_t id;
    // winning numbers
    std::vector<uint64_t> winningNums;
    // numbers that might match
    std::vector<uint64_t> nums;
    // count how many times card is in the stack
    uint64_t count;
};

int main()
{
    // open input file
    std::ifstream input;
    input.open("input.txt");
    std::string lineOfFile = "";

    // vector of all cards from input
    std::vector<cardStruct> cards;
    // final result that is displayed
    uint64_t final_sum = 0;

    // first get the inputs
    while (getline(input, lineOfFile))
    {
        // get all winning numbers and store them in a vector
        std::vector<uint64_t> winningNums;
        std::regex winningRegex("Card\\s+(\\d+):\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+");
        std::smatch matchesWinning;
        std::regex_search(lineOfFile, matchesWinning, winningRegex);
        for (uint64_t i = 2; i < matchesWinning.size(); i++)
        {
            // winning_nums.emplace_back(std::stoi(matchesWinning[i]));
            winningNums.emplace_back(std::stoi(matchesWinning[i]));
        }

        // id is the first regex match
        uint64_t id = std::stoi(matchesWinning[1]);

        // get all numbers and stopre them in a vector
        std::vector<uint64_t> nums;
        std::regex numbersRegex("\\|\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");
        std::smatch matchesNumbers;
        std::regex_search(lineOfFile, matchesNumbers, numbersRegex);
        for (uint64_t i = 1; i < matchesNumbers.size(); i++)
        {
            nums.emplace_back(std::stoi(matchesNumbers[i]));
        }

        // create struct with values that we got and store them in a vector
        cardStruct s = {id, winningNums, nums, 1};
        cards.emplace_back(s);
    }

    // close input file
    input.close();

    // iterate all found cards
    for (auto &card : cards)
    {
        // couter how many times we get a match in this card
        uint64_t roundpoints = 0;

        for (const uint64_t &winning : card.winningNums)
        {
            // find matches and count them
            if (std::find(card.nums.begin(), card.nums.end(), winning) != card.nums.end())
            {
                ++roundpoints;
            }
        }

        // duplicate cards - increase counter for cards underneath
        for (uint64_t i = 1; i <= roundpoints; i++)
        {
            // iterate the whole stack (optimization would be to start with the current card)
            for (auto &c : cards)
            {
                if (c.id == card.id + i)
                {
                    // if the id is matching increase the counter and break the loop
                    c.count += card.count;
                    break;
                }
            }
        }
    }

    // sum up all card counts
    for (auto &card : cards)
    {
        final_sum += card.count;
    }

    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
