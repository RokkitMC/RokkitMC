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

####JAVA
find_package(Java REQUIRED)
if(NOT ${Java_FOUND})
    message(FATAL_ERROR "Java 8 is required to build")
endif()
if(NOT ${Java_VERSION_MINOR} EQUAL 8)
    message(FATAL_ERROR "Java 8 is required to build, found Java ${Java_VERSION_MINOR}")
endif()
find_package(JNI REQUIRED)
if(NOT ${JNI_FOUND})
    message(FATAL_ERROR "JNI not found")
endif()
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources src/*.cpp include/*.h src/*.c include/*.hpp)
add_library(RokkitMC SHARED ${sources} include/Rokkit/RokkitServer.h src/Rokkit/RokkitServer.cpp)
message(${sources})
include_directories(lib/jsoncpp/include/json)
add_subdirectory(lib/jsoncpp)
target_link_libraries(RokkitMC PRIVATE subhook ${JNI_LIBRARIES} jsoncpp_lib)
