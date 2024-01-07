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


int main()
{
    uint64_t final_sum = 0;

    std::ifstream file("input.txt");
    std::string line;

    std::string directions = "LRLRLRRLRRRLRRRLRRRLRLRRRLRRRLRRRLLRLRRRLRLRRRLLRRRLRRLRRRLRRLRLRRRLRRRLRLRRLRRRLRRLRRRLRRLRLRRLRRRLRLRRLRRRLLRRRLRLRRLLLRLLRLRRLLRRRLLRLLRRLRLRRRLLLRLRRLRLRRLRRRLRRLLRRLLRLRRRLRRRLRLLLLRLLRLRLRLRRRLRRLRRLRLRRRLLRRLRLLRRLRLRRLRLRLRRLRRLLRLRRLLRLLRRRLLLRRRLRRLRLRRRLRRLRRRLRRLLLRRRR";

    std::map<std::string, node> tree;

    // read the tree for the game
    while (std::getline(file, line))
    {
        std::string name;
        node newNode;

        std::istringstream iss(line);
        iss >> name >> newNode.left >> newNode.right;

        tree.emplace(name, newNode);

        // std::cout << name << " " << newNode.left << " " << newNode.right << std::endl;
    }


    // try to figure out how many steps are needed beginning with AAA
    std::string current_node = "AAA";

    while (current_node != "ZZZ")
    {
        node current_node_info = tree.at(current_node);
        if (directions[final_sum%directions.length()] == 'L')
        {
            current_node = current_node_info.left;
            // std::cout << "Going left" << std::endl;
        }
        else
        {
            current_node = current_node_info.right;
            // std::cout << "Going right" << std::endl;
        }
        ++final_sum;
    }

    std::cout << "FINAL SUM " << final_sum << std::endl;
}
