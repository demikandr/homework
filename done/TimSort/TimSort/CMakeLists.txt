cmake_minimum_required(VERSION 2.8.4)
project(TimSort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
    TimSort.h)

set(SOURCE_FILES
    test.cxx)

add_executable(TimSort ${SOURCE_FILES})