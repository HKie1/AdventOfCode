#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

struct race
{
    uint64_t time;
    uint64_t distance;
};

int main()
{
    uint64_t final_sum = 0;
    std::vector<race> allRaces;

    allRaces.push_back({42, 308});
    allRaces.push_back({89, 1170});
    allRaces.push_back({91, 1291});
    allRaces.push_back({89, 1467});

    for (const auto& race_instance : allRaces)
    {
        uint64_t raceCount = 0;
        // std::cout << "TIME: " << race_instance.time << " DISTANCE: " << race_instance.distance << std::endl;

        for (uint64_t speed = 0; speed < race_instance.time; ++speed)
        {
            auto distance = speed * (race_instance.time - speed);
            if (distance > race_instance.distance)
            {
                // std::cout << distance << std::endl;
                raceCount++;
            }
        }
        // std::cout << "RACE COUNT: " << raceCount << std::endl;
        if (0 == final_sum)
        {
            final_sum = raceCount;
        }
        else
        {
            final_sum *= raceCount;
        }
    }


    std::cout << "FINAL ANSWER: " << final_sum << std::endl;
}
