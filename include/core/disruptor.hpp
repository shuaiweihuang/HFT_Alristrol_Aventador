#pragma once
#include <cstdint>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "market_data.hpp"

// 簡單 thread-safe queue 作為 Disruptor 骨架
class MarketDataDisruptor {
public:
    MarketDataDisruptor() = default;

    // 發布行情訊息
    void publish(const PriceUpdate& pu) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            queue_.push(pu);
        }
        cv_.notify_one();
    }

    // 消費行情訊息（阻塞直到有資料）
    PriceUpdate consume() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]{ return !queue_.empty(); });
        PriceUpdate pu = queue_.front();
        queue_.pop();
        return pu;
    }

    // 非阻塞消費
    bool try_consume(PriceUpdate& pu) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.empty()) return false;
        pu = queue_.front();
        queue_.pop();
        return true;
    }

private:
    std::queue<PriceUpdate> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

