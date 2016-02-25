cmake_minimum_required(VERSION 2.8.4)
project(TFrozenSet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    randomGen.h
    TFrozenSet.h
    test.cxx)

add_executable(TFrozenSet ${SOURCE_FILES})