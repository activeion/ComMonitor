cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

project(ComMonitor)

include_directories(${PROJECT_SOURCE_DIR}/gui/other
    ${PROJECT_SOURCE_DIR}/gui/inc)

#link_directories(${PROJECT_BINARY_DIR})


ADD_EXECUTABLE(com layout_snippet.cpp CSerial/Serial.cpp CSerial/SerialEx.cpp CSerial/SerialWnd.cpp)
Target_Link_Libraries(com Comctl32 libpthread.a)
