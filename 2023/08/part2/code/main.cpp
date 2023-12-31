#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

struct node
{
    std::string left;
    std::string right;
};

static uint64_t find_iter(std::string current_node, std::map<std::string, node> tree, std::string directions)
{
    uint64_t iterations = 0;
    while (current_node[2] != 'Z')
    {
        if (directions[iterations % directions.length()] == 'L')
        {
            current_node = tree.at(current_node).left;
            // std::cout << "Going left" << std::endl;
        }
        else
        {
            current_node = tree.at(current_node).right;
            // std::cout << "Going right" << std::endl;
        }
        ++iterations;
    }
    return iterations;
}

uint64_t greatestCommonDivisor(uint64_t a, uint64_t b)
{
    if (b == 0)
        return a;
    else
        return greatestCommonDivisor(b, a % b);
}

int main()
{
    uint64_t final_sum = 1;

    // std::ifstream file("input.txt");
    std::ifstream file("input.txt");
    std::string line;

    std::string directions = "LRLRLRRLRRRLRRRLRRRLRLRRRLRRRLRRRLLRLRRRLRLRRRLLRRRLRRLRRRLRRLRLRRRLRRRLRLRRLRRRLRRLRRRLRRLRLRRLRRRLRLRRLRRRLLRRRLRLRRLLLRLLRLRRLLRRRLLRLLRRLRLRRRLLLRLRRLRLRRLRRRLRRLLRRLLRLRRRLRRRLRLLLLRLLRLRLRLRRRLRRLRRLRLRRRLLRRLRLLRRLRLRRLRLRLRRLRRLLRLRRLLRLLRRRLLLRRRLRRLRLRRRLRRLRRRLRRLLLRRRR";

    std::map<std::string, node> tree;
    std::vector<std::string> startNodes;

    // read the tree for the game
    while (std::getline(file, line))
    {
        std::string name;
        node newNode;

        std::istringstream iss(line);
        iss >> name >> newNode.left >> newNode.right;

        tree.emplace(name, newNode);

        if (name[2] == 'A')
        {
            startNodes.push_back(name);
        }
    }

    std::cout << "Find the least common multiple of the following numbers: " << std::endl;
    for (auto c : startNodes)
    {
        uint64_t iter = find_iter(c, tree, directions);
        std::cout << iter << " ";

        // find current least common multiple
        final_sum = final_sum * iter / greatestCommonDivisor(final_sum, iter);
    }
    std::cout << std::endl;

    std::cout << "FINAL SUM " << final_sum << std::endl;
}
