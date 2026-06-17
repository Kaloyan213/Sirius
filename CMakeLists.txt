cmake_minimum_required(VERSION 3.20)
project(Sirius VERSION 1.0 LANGUAGES CXX)

# Set C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Handle output directories globally
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binaries)

# Add subdirectories
add_subdirectory(Sirius)
add_subdirectory(Sandbox)
