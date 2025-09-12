#pragma once
#include "market_data.hpp"
#include "disruptor.hpp"

class Strategy {
public:
    Strategy(MarketDataDisruptor& d) : disruptor(d) {}
    void run(); // 策略執行主循環
private:
    MarketDataDisruptor& disruptor;
};

