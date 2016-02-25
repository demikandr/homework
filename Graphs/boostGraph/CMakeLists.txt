cmake_minimum_required(VERSION 3.2)
project(boostGraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES untitled.cxx)
add_executable(boostGraph ${SOURCE_FILES})