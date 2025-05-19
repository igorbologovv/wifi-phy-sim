cmake_minimum_required(VERSION 3.10)
project(wifi_phy_sim)

add_executable(sim src/main.cpp src/qam.cpp)
target_include_directories(sim PRIVATE include)
