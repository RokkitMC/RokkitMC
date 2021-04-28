cmake_minimum_required(VERSION 3.16)
project(RokkitMC)

option(BUILD_TESTING off) #Stops subhook erroring due to no 64 bit test.

add_subdirectory(lib/subhook)
include_directories(lib/subhook)
include_directories(include)

####YASM
find_file(YASM_EXECUTABLE NAMES yasm yasm.exe)
if(NOT DEFINED YASM_EXECUTABLE)
    message(FATAL_ERROR "Yasm not found, required to compile")
endif()

set(CMAKE_CXX_STANDARD 20)

<<<<<<< HEAD
file(GLOB_RECURSE sources src/*.cpp include/*.h src/*.c include/*.hpp include/Rokkit/*.h include/Rokkit/*.hpp include/Rokkit/*.cpp)
add_library(RokkitMC SHARED ${sources})

=======
file(GLOB_RECURSE sources src/*.cpp include/*.h src/*.c include/*.hpp)
add_library(RokkitMC SHARED ${sources} include/Rokkit/RokkitServer.h src/Rokkit/RokkitServer.cpp)
message(${sources})
>>>>>>> 61944d51df3b3fb1aa885d943d691da0a8f4820b
include_directories(lib/jsoncpp/include/json)
add_subdirectory(lib/jsoncpp)
target_link_libraries(RokkitMC PRIVATE subhook ${JNI_LIBRARIES} jsoncpp_lib)