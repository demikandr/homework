cmake_minimum_required(VERSION 3.3)
project(MaxFlow)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -Wall -Wextra ")

set(SOURCE_FILES main.cpp network.h network.h)
add_executable(MaxFlow ${SOURCE_FILES})