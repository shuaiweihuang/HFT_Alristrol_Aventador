#include "network/feed_handler.hpp"
#include <thread>
#include <chrono>
#include <iostream>

void FeedHandler::run() {
    int count = 0;
    while (true) {
        PriceUpdate pu;
        pu.symbol = "AAPL";
        pu.bid = 150.0 + count * 0.1;
        pu.ask = 150.1 + count * 0.1;
        pu.last = 150.05 + count * 0.1;
        pu.volume = 100 + count;
        pu.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        disruptor.publish(pu);

        std::cout << "[Feed] Published price " << pu.last << std::endl;
        count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

