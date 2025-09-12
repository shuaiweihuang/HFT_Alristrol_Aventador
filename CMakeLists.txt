cmake_minimum_required(VERSION 3.20)
project(HFTProject VERSION 1.0 LANGUAGES CXX)

# -----------------------------
# 1. 編譯設定
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# -----------------------------
# 2. include 路徑
# -----------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# -----------------------------
# 3. 尋找依賴 (Boost / MemSQL / GTest)
# -----------------------------
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(/usr/local/include/memsql)
link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)


# -----------------------------
# 4. 檢查 MemSQL library (Optional)
# -----------------------------
set(MEMSQL_FOUND FALSE)
find_library(MEMSQL_LIB memsqlclient PATHS /usr/local/lib)
if(MEMSQL_LIB)
    message(STATUS "Found MemSQL client: ${MEMSQL_LIB}")
    include_directories(/usr/local/include/memsqlclient)
    set(MEMSQL_FOUND TRUE)
else()
    message(WARNING "MemSQL client library not found. Skipping MemSQL linking.")
endif()

# -----------------------------
# 5. 源碼檔案
# -----------------------------
file(GLOB_RECURSE CORE_SOURCES src/core/*.cpp)
file(GLOB_RECURSE COMMON_SOURCES src/common/*.cpp)
file(GLOB_RECURSE NETWORK_SOURCES src/network/*.cpp)

set(SRC_FILES
    src/main.cpp
    ${CORE_SOURCES}
    ${COMMON_SOURCES}
    ${NETWORK_SOURCES}
)

# -----------------------------
# 6. 建立 bin 資料夾並放置可執行檔
# -----------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(hft_project ${SRC_FILES})

set(LINK_LIBS ${Boost_LIBRARIES} pthread)

if(MEMSQL_FOUND)
    list(APPEND LINK_LIBS ${MEMSQL_LIB})
endif()

target_link_libraries(hft_project ${LINK_LIBS})

# -----------------------------
# 7. 單元測試
# -----------------------------
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

if(TEST_SOURCES)
    add_executable(run_tests ${TEST_SOURCES} ${CORE_SOURCES} ${COMMON_SOURCES} ${NETWORK_SOURCES})
    target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
    add_test(NAME HFTTests COMMAND run_tests)
endif()

# -----------------------------
# 8. 編譯選項
# -----------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(hft_project PRIVATE -O3 -march=native -funroll-loops)
else()
    target_compile_options(hft_project PRIVATE -g -Wall -Wextra -O0)
endif()

