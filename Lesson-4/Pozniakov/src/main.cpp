#include <iostream>
#include <unordered_map>
#include "OpenWeatherMapClient.h"

int main()
{
    OpenWeatherMapClient weatherMapClient;
    auto data = weatherMapClient.getCurrenWeatherData("Odesa");
    for(const auto& item : data)
    {
        std::cout << item.first << ": " << item.second << std::endl;
    }

    return 0;
}
