cmake_minimum_required(VERSION 3.10)
project(wifi_phy_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sim
    src/main.cpp
    src/mcs.cpp
    src/qam.cpp
    src/phy.cpp
)

target_include_directories(sim PRIVATE include)
