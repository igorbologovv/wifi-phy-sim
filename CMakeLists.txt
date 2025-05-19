cmake_minimum_required(VERSION 3.10)
project(wifi_ofdm_phy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    /usr/include/eigen3
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(sim
    src/main.cpp
    src/mcs.cpp
    src/qam.cpp
    src/phy.cpp
    src/ofdm.cpp          # новый файл с FFT/IFFT
)


