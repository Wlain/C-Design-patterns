cmake_minimum_required(VERSION 3.20)
project(cppDesignPatterns)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# execute genDocs script
execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/docs/source/genDocs.sh)

add_executable(cppDesignPatterns ${SOURCES})

