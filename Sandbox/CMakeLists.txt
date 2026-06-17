file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.h" "include/*.cpp" "include/*.h")

add_executable(Sandbox ${SOURCES})

target_link_libraries(Sandbox PRIVATE Sirius)

target_include_directories(Sandbox PRIVATE 
    "include"
    "${CMAKE_SOURCE_DIR}/Sirius/include"
    "${CMAKE_SOURCE_DIR}/Sirius/third-party/spdlog/include"
)

target_compile_definitions(Sandbox PRIVATE 
    $<$<CONFIG:Debug>:SIRIUS_DEBUG>
    $<$<CONFIG:Release>:SIRIUS_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:SIRIUS_DIST>
)

if(WIN32)
    target_compile_definitions(Sandbox PRIVATE SIRIUS_PLATFORM_WINDOWS)
    target_compile_options(Sandbox PRIVATE /utf-8)
    
    # Post-build command to copy DLL
    add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:Sirius>" "$<TARGET_FILE_DIR:Sandbox>/"
    )
endif()
