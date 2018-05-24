
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
ADD_EXECUTABLE(test test.cpp)

Target_Link_Libraries(test Comctl32)




