cmake_minimum_required(VERSION 3.16)
project(RokkitMC)

set(BUILD_TESTING off) #Stops subhook erroring due to no 64 bit test
add_subdirectory(./lib/subhook)
include_directories(./lib/subhook)

set(CMAKE_CXX_STANDARD 20)

add_executable(RokkitMC src/main.cpp src/definitions.h)

target_link_libraries(RokkitMC PRIVATE subhook)