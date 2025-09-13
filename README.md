MIT License

Copyright (c) 2025 Alristrol Technologies Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


Overview
This project implements a 'high-frequency trading architecture' optimized for ultra-low latency and high throughput.  
It is built with 'C/C++' for performance-critical modules, applies the 'LMAX Disruptor' pattern for lock-free inter-thread communication, and integrates 'MemSQL' for distributed in-memory storage and real-time analytics.  

The architecture is designed to handle large volumes of market data, process strategies in microseconds, and execute orders at scale.

Key Features
- 'Ultra-Low Latency': Microsecond-level event handling using C/C++.
- 'High Throughput': LMAX Disruptor for lock-free messaging.
- 'Real-Time Analytics': MemSQL for in-memory, distributed query execution.
- 'Scalability': Horizontal scaling for multiple market feeds and order flows.
- 'Modular Design': Clear separation of concerns for market data, strategy, order management, and storage.

Prerequisites
- GCC 11+ / Clang 14+
- CMake 3.20+
- MemSQL client library
- Boost (for networking utilities)
- GoogleTest (for unit tests)

Build
```bash
mkdir build && cd build
cmake ..
make -j4
```

Project Structure
/HFT_Alristrol_Aventador
├── CMakeLists.txt              # 編譯設定
├── README.md                   # 專案說明
│
├── include/                    # 標頭檔 (.h/.hpp)
│   ├── common/                 # 公用工具
│   │   ├── config.hpp
│   │   ├── logger.hpp
│   │   └── utils.hpp
│   ├── core/                   # 核心模組介面
│   │   ├── market_data.hpp
│   │   ├── disruptor.hpp
│   │   ├── strategy.hpp
│   │   ├── order_manager.hpp
│   │   └── storage.hpp
│   └── network/                # 網路相關
│       ├── feed_handler.hpp
│       └── tcp_client.hpp
│
├── src/                        # 主要程式碼
│   ├── main.cpp                # 進入點
│   │
│   ├── common/
│   │   ├── config.cpp
│   │   ├── logger.cpp
│   │   └── utils.cpp
│   │
│   ├── core/
│   │   ├── market_data.cpp     # 行情解析與分發
│   │   ├── disruptor.cpp       # LMAX disruptor 實作
│   │   ├── strategy.cpp        # 策略核心邏輯
│   │   ├── order_manager.cpp   # 訂單管理與下單
│   │   └── storage.cpp         # 與 MemSQL 互動
│   │
│   └── network/
│       ├── feed_handler.cpp    # 行情來源處理
│       └── tcp_client.cpp      # 與交易所連線
│
├── tests/                      # 單元測試
│   ├── test_market_data.cpp
│   ├── test_strategy.cpp
│   └── test_order_manager.cpp
│
└── scripts/                    # 工具腳本
    ├── run.sh
    ├── deploy.sh
    └── benchmark.py            # 測試延遲/吞吐

Roadmap
* [ ] Add multiple market feed adapters 
* [ ] Implement additional trading strategies
* [ ] Integrate FPGA acceleration layer
* [ ] Expand risk management and monitoring
