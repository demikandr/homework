cmake_minimum_required(VERSION 2.8.4)
project(TTopElements)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    "TTopElements(line).cxx")

set(SOURCE_FILES
    "test.cxx")

add_executable(TTopElements ${SOURCE_FILES})