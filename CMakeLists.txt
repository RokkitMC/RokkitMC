cmake_minimum_required(VERSION 3.17)
project(RokkitMC)

add_subdirectory(./lib/subhook)
include_directories(./lib/subhook)

set(CMAKE_CXX_STANDARD 20)

add_executable(RokkitMC main.cpp)

target_link_libraries(RokkitMC PRIVATE subhook)