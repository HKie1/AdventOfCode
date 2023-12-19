#include <iostream>
#include <vector>
#include <fstream>

using gearList = std::vector<int>;
std::vector<std::vector<gearList>> gearToNums;

static int64_t getNumLength(int num)
{
    int64_t numLength = 1;
    int64_t temp = num;
    while ((temp /= 10) != 0)
    {
        numLength++;
    }
    return numLength;
}

// return  0 if not a number
//        -1 if middle of a number
//        -2 if not a part number
static int getPartNumber(const std::vector<std::string> &lines, int i, int j)
{
    int num;
    if (!isdigit(lines[i][j]) || sscanf(lines[i].c_str() + j, "%d", &num) != 1)
    {

        return 0;
    }

    // not the beginning
    if (j > 0 && isdigit(lines[i][j - 1]))
    {
        return -1;
    }
    int numLength = getNumLength(num);

    bool bingo = false;
    for (int r = i - 1; r <= i + 1; r++)
    {
        for (int c = j - 1; c <= j + numLength; c++)
        {
            if (r < 0 || r >= static_cast<int>(lines.size()))
            {
                continue;
            }
            if (c < 0 || c >= static_cast<int>(lines[i].size()))
            {
                continue;
            }
            char ch = lines[r][c];

            // bingo
            if (ch != '.' && !isdigit(ch))
            {
                bingo = true;
            }
        }
    }

    if (!bingo)
        return -2;

    // populate the map
    for (int r = i - 1; r <= i + 1; r++)
    {
        for (int c = j - 1; c <= j + numLength; c++)
        {
            if (r < 0 || r >= static_cast<int>(lines.size()))
            {
                continue;
            }
            if (c < 0 || c >= static_cast<int>(lines[i].size()))
            {
                continue;
            }
            char ch = lines[r][c];
            if (ch == '*')
            {
                gearToNums[r][c].push_back(num);
            }
        }
    }

    return num;
}

int main()
{
    std::vector<std::string> lines;
    std::string lineOfFile;
    // open input file
    std::ifstream input;
    input.open("input.txt");

    while (getline(input, lineOfFile))
    {
        lines.push_back(lineOfFile);
    }

    gearToNums.resize(lines.size());
    for (auto &row : gearToNums)
    {
        row.resize(lines[0].size());
    }

    // dummy loop to populate the global map
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::string line = lines[i];
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            getPartNumber(lines, i, j);
        }
    }

    int total = 0;
    for (size_t i = 0; i < lines.size(); i++)
    {
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '*')
            {
                const auto &currentGearList = gearToNums[i][j];
                if (currentGearList.size() == 2)
                {
                    total += currentGearList[0] * currentGearList[1];
                }
            }
        }
    }

    std::cout << total << std::endl;
}
