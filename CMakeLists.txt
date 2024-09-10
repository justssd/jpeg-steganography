cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(jpeg-steganography LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

include(Sanitizers.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall")

add_library(jdct_h lib/jdct.cpp)

add_executable(test_jdct_h tests/test_jdct_h.cpp)
target_link_libraries(test_jdct_h jdct_h jpeg)

add_executable(js src/js.cpp)
target_link_libraries(js jpeg)
