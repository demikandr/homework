cmake_minimum_required(VERSION 3.2)
project(MST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    BoostKruskal.cxx)

add_executable(MST ${SOURCE_FILES})