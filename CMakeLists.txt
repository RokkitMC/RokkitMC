cmake_minimum_required(VERSION 3.16)
project(RokkitMC)

set(BUILD_TESTING off) #Stops subhook erroring due to no 64 bit test
add_subdirectory(lib/subhook)
include_directories(lib/subhook)
include_directories(include)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources "src/*.cpp" "include/*.h" "src/*.c" "include/*.hpp")

add_library(RokkitMC SHARED ${sources} include/hooks.h include/logger.h)

target_link_libraries(RokkitMC PRIVATE subhook)