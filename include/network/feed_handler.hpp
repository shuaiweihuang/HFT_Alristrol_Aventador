#pragma once
#include "core/disruptor.hpp"
#include "core/market_data.hpp"

class FeedHandler {
public:
    FeedHandler(MarketDataDisruptor& d) : disruptor(d) {}
    void run();
private:
    MarketDataDisruptor& disruptor;
};

