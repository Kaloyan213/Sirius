file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.h" "include/*.h")

add_library(Sirius SHARED ${SOURCES})

target_include_directories(Sirius PUBLIC 
    "include"
    "third-party/spdlog/include"
)

target_compile_definitions(Sirius PUBLIC 
    $<$<CONFIG:Debug>:SIRIUS_DEBUG>
    $<$<CONFIG:Release>:SIRIUS_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:SIRIUS_DIST>
)

if(WIN32)
    target_compile_definitions(Sirius PRIVATE SIRIUS_PLATFORM_WINDOWS SIRIUS_BUILD_DLL)
    target_compile_options(Sirius PRIVATE /utf-8)
endif()
