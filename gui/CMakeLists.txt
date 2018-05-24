cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

project(gui)

include_directories(
	#${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/other
)

link_directories(
	${PROJECT_BINARY_DIR}
)

subdirs(test)







