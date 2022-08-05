cmake_minimum_required(VERSION 3.20)
project(cppDesignPatterns)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(cppDesignPatterns ${SOURCES})
