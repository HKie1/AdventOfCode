#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

std::string STRENGTH = "23456789TJQKA";

// STRONG
// 5 of a kind - 55555
// 4 of a kind - 44442
// full house - 44422
// 3 of a kind - 33322
// 2 pairs - 22334
// 1 pair - 22345
// highest card - A2345
// WEAK



struct PlayerHand
{
    std::string hand;
    uint64_t bid;
    uint32_t category;
    uint32_t place;
};

void cathegorizeHand(PlayerHand &playerHand)
{
    std::string hand = playerHand.hand;

    // 5 of a kind - 7
    if (hand[0] == hand[1] && hand[1] == hand[2] && hand[2] == hand[3] && hand[3] == hand[4])
    {
        playerHand.category = 7;
        return;
    }


    // 4 of a kind - 6
    std::sort(hand.begin(), hand.end(), [](char a, char b) {
        return STRENGTH.find(a) < STRENGTH.find(b);
    });
    std::regex fourOfAKindRegex("([23456789TJQKA])\\1{3}");
    std::smatch fourOfAKindMatch;
    if (std::regex_search(playerHand.hand, fourOfAKindMatch, fourOfAKindRegex))
    {
        playerHand.category = 6;
        return;
    }


    // full house - 5
    std::sort(hand.begin(), hand.end(), [](char a, char b) {
        return STRENGTH.find(a) < STRENGTH.find(b);
    });
    if (
        (hand[0] == hand[1] && hand[1] == hand[2] && hand[3] == hand[4])
        ||
        (hand[0] == hand[1] && hand[2] == hand[3] && hand[3] == hand[4])
    )
    {
        playerHand.category = 5;
        return;
    }



    // 3 of a kind - 4
    std::sort(hand.begin(), hand.end(), [](char a, char b) {
        return STRENGTH.find(a) < STRENGTH.find(b);
    });
    std::regex threeOfAKindRegex("([23456789TJQKA])\\1{2}");
    std::smatch threeOfAKindMatch;
    if (std::regex_search(hand, threeOfAKindMatch, threeOfAKindRegex))
    {
        playerHand.category = 4;
        return;
    }


    // 2 pairs - 3
    std::sort(hand.begin(), hand.end(), [](char a, char b) {
        return STRENGTH.find(a) < STRENGTH.find(b);
    });
    std::regex twoPairsRegex("([23456789TJQKA])\\1{1}.*([23456789TJQKA])\\2");
    std::smatch twoPairsMatch;
    if (std::regex_search(hand, twoPairsMatch, twoPairsRegex))
    {
        playerHand.category = 3;
        return;
    }


    // 1 pair - 2
    std::sort(hand.begin(), hand.end(), [](char a, char b) {
        return STRENGTH.find(a) < STRENGTH.find(b);
    });
    std::regex pairRegex("([23456789TJQKA])\\1");
    std::smatch pairMatch;
    if (std::regex_search(hand, pairMatch, pairRegex))
    {
        playerHand.category = 2;
        return;
    }


    // highest card - 1
    playerHand.category = 1;
    return;


}


void sort(std::vector<PlayerHand> &hands)
{
    std::sort(hands.begin(), hands.end(), [](PlayerHand a, PlayerHand b) {
        // iterate hand
        for(size_t i = 0; i < a.hand.length(); ++i)
        {
            if (a.hand[i] == b.hand[i])
            {
                continue;
            }
            else
            {
                return STRENGTH.find(a.hand[i]) > STRENGTH.find(b.hand[i]);
            }
        }
        return false;
    });
}

int main()
{
    uint64_t final_sum = 0;

    uint16_t lines = 0;
    std::ifstream file("input_test.txt");
    std::vector<PlayerHand> hands;
    std::vector<PlayerHand> cat7;
    std::vector<PlayerHand> cat6;
    std::vector<PlayerHand> cat5;
    std::vector<PlayerHand> cat4;
    std::vector<PlayerHand> cat3;
    std::vector<PlayerHand> cat2;
    std::vector<PlayerHand> cat1;
    
    std::string line;

    while (std::getline(file, line))
    {
        lines++;
        PlayerHand playerHand;
        std::istringstream iss(line);
        iss >> playerHand.hand >> playerHand.bid;
        playerHand.category = 0;
        playerHand.place = 0;
        hands.push_back(playerHand);
    }

    for (auto& playerHand : hands)
    {
        cathegorizeHand(playerHand);
    }

    std::sort(hands.begin(), hands.end(), [](PlayerHand a, PlayerHand b) {
        return a.category > b.category;
    });

    for (size_t i = 0; i < hands.size(); ++i)
    {
        switch (hands[i].category)
        {
            case 1:
                cat1.push_back(hands[i]);
                break;

            case 2:
                cat2.push_back(hands[i]);
                break;
            
            case 3:
                cat3.push_back(hands[i]);
                break;

            case 4:
                cat4.push_back(hands[i]);
                break;

            case 5:
                cat5.push_back(hands[i]);
                break;

            case 6:
                cat6.push_back(hands[i]);
                break;

            case 7:
                cat7.push_back(hands[i]);
                break;
            
            default:
                break;
        }
    }

    // apply sort on all cat vectors
    sort(cat7);
    sort(cat6);
    sort(cat5);
    sort(cat4);
    sort(cat3);
    sort(cat2);
    sort(cat1);

    for (auto& playerHand : cat7)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat6)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat5)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat4)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat3)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat2)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    for (auto& playerHand : cat1)
    {
        playerHand.place = lines--;
        final_sum += playerHand.place * playerHand.bid;
        std::cout << playerHand.hand << " " << playerHand.bid << " " << playerHand.category << " " << playerHand.place << std::endl;
    }

    file.close();

    std::cout << "final sum: " << final_sum << std::endl;
    // 6592
}
