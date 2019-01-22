cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)

project (Foo VERSION 1.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(numplib ${SRC_FILES})
add_executable(Foo ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(Foo numplib)

add_subdirectory(packages/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
message(${PROJECT_SOURCE_DIR}/test/)
add_executable(runUnitTests ${TEST_SRC_FILES})
target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests numplib)
add_test(UnitTests runUnitTests)