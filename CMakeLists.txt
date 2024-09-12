cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(jpeg-steganography LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

include(Sanitizers.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall")

add_library(jdct_h lib/jdct.cpp)
add_library(jsteg_h lib/jsteg.cpp)

add_executable(js src/js.cpp)
target_link_libraries(js jpeg jdct_h jsteg_h)
