#pragma once
#include <string>
#include <cstdint>

struct PriceUpdate {
    std::string symbol;
    double bid;
    double ask;
    double last;
    int volume;
    uint64_t timestamp;
};
