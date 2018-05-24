cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

project(ComMonitor)

include_directories(${PROJECT_SOURCE_DIR}/gui/other ${PROJECT_SOURCE_DIR}/gui/inc)

#link_directories(${PROJECT_BINARY_DIR})


ADD_EXECUTABLE(com ComMonitor.cpp)
Target_Link_Libraries(com Comctl32)
