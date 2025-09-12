#include "core/disruptor.hpp"
#include "core/strategy.hpp"
#include "network/feed_handler.hpp"
#include <thread>


int main() {
    MarketDataDisruptor disruptor;

    FeedHandler feed(disruptor);
    Strategy strategy(disruptor);

    std::thread feedThread([&](){ feed.run(); });
    std::thread strategyThread([&](){ strategy.run(); });

    feedThread.join();
    strategyThread.join();

    return 0;
}
