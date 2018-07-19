cmake_minimum_required(VERSION 2.8)

# Project name.
project(SimpleNumberSearch)
# Find required Threads package.
find_package(Threads REQUIRED)
# Complie with thread support, all warnings and maximum optimisation.
set(CMAKE_CXX_FLAGS "-pthread -Wall -o3")
# Set variable of all sources to compile.
set( project_sources
   main.cpp
   XMLReader.cpp
   XMLProcessor.cpp
   PrimeNumberSearchEngine.cpp
   XMLParcer.cpp
)
# Set target name and included sources.
add_executable(${PROJECT_NAME} ${project_sources})
