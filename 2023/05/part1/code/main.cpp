#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>

struct Mapping
{
    int64_t destinationRangeStart;
    int64_t sourceRangeStart;
    int64_t rangeLength;
};

std::vector<long long> getSeeds()
{
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);

    std::string trash;
    ss >> trash;

    std::vector<long long> seeds;
    long long s;
    while (ss >> s)
        seeds.push_back(s);

    getline(std::cin, trash);

    return seeds;
}

std::vector<Mapping> getMap()
{
    std::vector<Mapping> mapping;

    std::string line;
    while (getline(std::cin, line) && line != "")
    {
        std::stringstream ss(line);

        long long dest, src, range;
        while (ss >> dest >> src >> range)
            mapping.push_back({dest, src, range});
    }

    return mapping;
}

int64_t findInMapping(int64_t lookUpNumber, std::vector<Mapping> mapping)
{
    for (const auto &map : mapping)
    {
        if (lookUpNumber > map.sourceRangeStart && lookUpNumber <= map.sourceRangeStart + map.rangeLength)
        {
            return map.destinationRangeStart + lookUpNumber - map.sourceRangeStart;
        }
    }
    return lookUpNumber;
}

int main()
{
    int64_t final_sum = 0;

    std::vector<int64_t> results;

    std::vector<long long> seeds = getSeeds();
    std::vector<Mapping> mp1 = getMap();
    std::vector<Mapping> mp2 = getMap();
    std::vector<Mapping> mp3 = getMap();
    std::vector<Mapping> mp4 = getMap();
    std::vector<Mapping> mp5 = getMap();
    std::vector<Mapping> mp6 = getMap();
    std::vector<Mapping> mp7 = getMap();

    final_sum = __LONG_LONG_MAX__;
    for (const auto &seed : seeds)
    {
        auto res = seed;
        res = findInMapping(seed, mp1);
        res = findInMapping(res, mp2);
        res = findInMapping(res, mp3);
        res = findInMapping(res, mp4);
        res = findInMapping(res, mp5);
        res = findInMapping(res, mp6);
        res = findInMapping(res, mp7);
        std::cout << "Location " << res << std::endl;
        final_sum = res < final_sum ? res : final_sum;
    }

    std::cout << "###########\nFINAL ANSWER: " << final_sum << std::endl;
}
