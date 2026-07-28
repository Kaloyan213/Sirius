# Gather source files
file(GLOB_RECURSE SOURCES "include/*.h" "source/*.h" "source/*.cpp")

# Create Shared Library
add_library(Sirius SHARED ${SOURCES})

# Include Directories
# PUBLIC means anyone linking to Sirius will also get these include paths.
target_include_directories(Sirius 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/spdlog/include
)

# Definitions specific to Sirius
target_compile_definitions(Sirius PRIVATE SIRIUS_BUILD_DLL)
