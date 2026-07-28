# Gather source files
file(GLOB_RECURSE SOURCES "include/*.h" "include/*.cpp" "source/*.h" "source/*.cpp")

set(SANDBOX_NAME "sandbox-app")

# Create Executable
add_executable(${SANDBOX_NAME} ${SOURCES})

# Include Directories (Sirius/include is automatically inherited)
target_include_directories(${SANDBOX_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        # Referencing the third-party folder inside Sirius:
        ${CMAKE_SOURCE_DIR}/Sirius/third-party/spdlog/include
)

# Link against Sirius
target_link_libraries(${SANDBOX_NAME} PRIVATE Sirius)
