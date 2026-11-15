#pragma once

#include <map>
#include <string_view>
#include <string>


inline const std::map<std::string, int> input_map{
    {"quit", 0},
    {"help", 1},
    {"grab", 2},
    {"restore", 3},
    {"auto-grab", 4},
    {"auto-grab-time", 5}
};

const int get_code(const std::string_view input) {
    const auto it{input_map.find(std::string(input))};

    if(it == input_map.end()) {
        return -1;
    }
    
    return it->second;
}