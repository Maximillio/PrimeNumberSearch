cmake_minimum_required(VERSION 2.8)

# Project name.
project(SimpleNumberSearchTestCases)
#Find required Threads and Google Test packages.
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
# Complie with thread support, all warnings and maximum optimisation.
set(CMAKE_CXX_FLAGS "-pthread -Wall -o3")
# Set variable of all sources to compile.
set(project_sources
   main.cpp
   XMLReaderTestCases.cpp
   XMLProcessorTestCases.cpp
   PrimeNumberSearchEngineTestCases.cpp
   XMLParcerTestCases.cpp)
# Set target name and included sources.
add_executable(${PROJECT_NAME} ${project_sources})
# Link precompiled Google Test library files to project executable.
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})



