cmake_minimum_required(VERSION 3.2)

project(Tests VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()
include(CTest)

set(TEST_HEADER ${CMAKE_SOURCE_DIR}/Tests/include)

set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

##################### Test Vector ##################################
set(VECTOR_TEST_FILE ${CMAKE_SOURCE_DIR}/Tests/Vector/TestVec3D.cpp)

add_executable(Vector ${VECTOR_TEST_FILE})
target_include_directories(Vector 
    PUBLIC 
        ${HEADER_DIR} 
        ${TEST_HEADER}
)

##################### Test Color ###################################
set(COLOR_SRC_FILE ${CMAKE_SOURCE_DIR}/src/Color.cpp)
set(COLOR_TEST_FILE ${CMAKE_SOURCE_DIR}/Tests/Color/TestColor.cpp)

add_executable(Color ${COLOR_TEST_FILE} ${COLOR_SRC_FILE})
target_include_directories(Color 
    PUBLIC 
        ${HEADER_DIR} 
        ${TEST_HEADER}
)

add_test(TestVector Vector)
add_test(TestColor Color)