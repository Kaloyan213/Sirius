# Gather source files
file(GLOB_RECURSE SOURCES "include/*.h" "source/*.h" "source/*.cpp")

set(SANDBOX_NAME "sandbox-app")

# Create Executable
add_executable(${SANDBOX_NAME} ${SOURCES})

target_include_directories(${SANDBOX_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against Sirius
target_link_libraries(${SANDBOX_NAME} PRIVATE Sirius)
