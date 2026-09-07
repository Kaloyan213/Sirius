set (ENGINE_NAME "Sirius")
# Gather source files (See note below about GLOB)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "include/*.h" "source/*.h" "source/*.cpp")

# Create Shared Library
add_library(${ENGINE_NAME} SHARED ${SOURCES})

# Include Directories
target_include_directories(${ENGINE_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/spdlog/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

# Generate export header
include(GenerateExportHeader)
generate_export_header(${ENGINE_NAME}
    EXPORT_MACRO_NAME SIRIUS_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/sirius_export.h
)

target_compile_definitions(${ENGINE_NAME} 
    PRIVATE 
        SIRIUS_BINARY_DIR=\"${CMAKE_BINARY_DIR}\"
)

add_subdirectory(configs)

