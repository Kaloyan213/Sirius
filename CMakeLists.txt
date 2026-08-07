cmake_minimum_required(VERSION 3.16)

# Set a default build type if none is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build: Debug Release Distribution" FORCE)
endif()

project(SiriusWorkspace VERSION 1.0.0 LANGUAGES CXX)

# Global settings inspired by your reference
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

# Consolidate all binary outputs to a single directory to avoid post-build copy scripts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Common Compile Options based on Platform and Build Type
if(MSVC)
    add_compile_options(/utf-8 /MP /W4)
    add_compile_definitions(SIRIUS_PLATFORM_WINDOWS)
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_definitions(SIRIUS_DEBUG)
    elseif(CMAKE_BUILD_TYPE MATCHES "^(Release|Distribution)$")
        add_compile_definitions($<$<CONFIG:Release>:SIRIUS_RELEASE> $<$<CONFIG:Distribution>:SIRIUS_DIST>)
        add_compile_options(/O2)
    endif()
else()
    # Unix-like compiler flags
    add_compile_options(-fPIC -Wall -Wextra -Wpedantic -fvisibility=hidden)
    add_compile_definitions(SIRIUS_PLATFORM_LINUX)
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_definitions(SIRIUS_DEBUG)
        add_compile_options(-O0 -g3)
    elseif(CMAKE_BUILD_TYPE MATCHES "^(Release|Distribution)$")
        add_compile_definitions($<$<CONFIG:Release>:SIRIUS_RELEASE> $<$<CONFIG:Distribution>:SIRIUS_DIST>)
        add_compile_options(-O3)
    else()
        message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

# Subdirectories containing the actual engine
add_subdirectory(SiriusEngine)
add_subdirectory(SandboxApp)
