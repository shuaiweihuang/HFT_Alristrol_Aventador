// src/core/strategy.cpp
#include "core/strategy.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void Strategy::run() {
    while (true) {
        PriceUpdate pu = disruptor.consume();
        std::cout << "[Strategy] Consumed price for " << pu.symbol 
                  << " last=" << pu.last << std::endl;
    }
}
