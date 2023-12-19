#include <iostream>
#include <vector>
#include <sstream>
#include <cstdint>
#include <algorithm>

#include <cassert>
#include <climits>

#define REPORT(X) std::cout << "(" << __LINE__ << ") " << #X << " = " << (X) << std::endl

struct Mapping
{
    uint64_t dest;
    uint64_t src;
    uint64_t range;
};

static std::vector<std::pair<uint64_t, uint64_t>> getSeedRanges()
{
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);

    std::string trash;
    ss >> trash;

    std::vector<std::pair<uint64_t, uint64_t>> seedRanges;
    int64_t start, range;
    while (ss >> start >> range)
    {
        seedRanges.push_back({ start, range });
    }

    getline(std::cin, trash);

    return seedRanges;
}

static std::vector<Mapping> getMap()
{
    std::vector<Mapping> mapping;

    std::string line;
    while (getline(std::cin, line) && line != "")
    {
        std::stringstream ss(line);

        uint64_t dest, src, range;
        while (ss >> dest >> src >> range)
            mapping.push_back({ dest, src, range });
    }

    return mapping;
}

static uint64_t printRanges(const std::vector<std::pair<uint64_t, uint64_t>>& keyRanges)
{
    uint64_t total = 0;

    for (const auto& range : keyRanges)
    {
        total += range.second;
    }

    return total;
}

static std::vector<std::pair<uint64_t, uint64_t>> lookUp(std::vector<std::pair<uint64_t, uint64_t>> keyRanges, std::vector<Mapping> mp)
{
    std::vector<std::pair<uint64_t, uint64_t>> results;

    uint64_t totalBefore = printRanges(keyRanges);

    uint64_t totalAfter = 0;
    for (const auto& keyRange : keyRanges)
    {
        uint64_t minKey = keyRange.first;
        uint64_t maxKey = minKey + keyRange.second - 1;

        std::vector<std::pair<uint64_t, uint64_t>> usedRanges;

        for (const auto& mapping : mp)
        {
            uint64_t minMapping = mapping.src;
            uint64_t maxMapping = mapping.src + mapping.range - 1;
            // no overlap
            if (minMapping > maxKey || minKey > maxMapping)
            {
                continue;
            }

            uint64_t minResult = std::max(minKey, minMapping);
            uint64_t maxResult = std::min(maxKey, maxMapping);
            usedRanges.push_back({ minResult, maxResult });
            uint64_t range = maxResult - minResult + 1;

            uint64_t delta = mapping.dest - mapping.src;
            results.push_back({ minResult + delta, range });
            REPORT(results.size());
        }

        sort(usedRanges.begin(), usedRanges.end());
        REPORT(usedRanges.size());
        uint64_t start = minKey;
        for (const auto& usedRange : usedRanges)
        {
            if (start < usedRange.first)
            {
                results.push_back({ start, usedRange.first - start });
            }

            start = usedRange.second + 1;
        }
        REPORT(std::endl);
        if (start <= maxKey)
        {
            results.push_back({ start, maxKey - start + 1 });
        }

        totalAfter = printRanges(results);
        REPORT(totalAfter);
    }
    assert(totalBefore == totalAfter);
    return results;
}

static uint64_t getMin(uint64_t current, const std::vector<std::pair<uint64_t, uint64_t>>& ranges)
{
    uint64_t ans = current;
    for (const auto& range : ranges)
    {
        ans = std::min(ans, range.first);
    }
    return ans;
}

int main()
{
    std::vector<std::pair<uint64_t, uint64_t>> seedRanges = getSeedRanges();
    std::vector<Mapping> mp1 = getMap();
    std::vector<Mapping> mp2 = getMap();
    std::vector<Mapping> mp3 = getMap();
    std::vector<Mapping> mp4 = getMap();
    std::vector<Mapping> mp5 = getMap();
    std::vector<Mapping> mp6 = getMap();
    std::vector<Mapping> mp7 = getMap();

    uint64_t ans = LONG_LONG_MAX;
    for (const auto& seedRange : seedRanges) {
        const auto soil = lookUp({ seedRange }, mp1);
        REPORT(soil.size());
        const auto fertilizer = lookUp(soil, mp2);
        const auto water = lookUp(fertilizer, mp3);
        const auto light = lookUp(water, mp4);
        const auto temperature = lookUp(light, mp5);
        const auto humidity = lookUp(temperature, mp6);
        const auto location = lookUp(humidity, mp7);
        ans = getMin(ans, location);
        REPORT(ans);
    }

    std::cout << ans << std::endl;
}
