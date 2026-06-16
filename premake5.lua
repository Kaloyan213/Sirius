workspace "Sirius"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

multiprocessorcompile "On"

project "Sirius"
    location "Sirius"
    kind "SharedLib"
    language "C++"
    buildoptions "/utf-8"

    targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/third-party/spdlog/include",
        "%{prj.name}/include"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} \"../binaries/" .. outputdir .. "/Sandbox/\"")
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

        defines {
            "SIRIUS_PLATFORM_WINDOWS",
            "SIRIUS_BUILD_DLL"
        }

     filter "configurations:Debug"
        defines "SIRIUS_DEBUG"
        symbols "On"

     filter "configurations:Release"
        defines "SIRIUS_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "SIRIUS_DIST"
        optimize "On"

project "Sandbox"    
    location "Sirius"
    kind "ConsoleApp"
    language "C++"
    buildoptions "/utf-8"

    targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.cpp",
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp",
    }

    includedirs
    {
        "Sirius/third-party/spdlog/include",
        "%{prj.name}/include",
        "Sirius/include"
    }

    links 
    {
        "Sirius"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

        defines {
            "SIRIUS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SIRIUS_DEBUG"
        symbols "On"

     filter "configurations:Release"
        defines "SIRIUS_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "SIRIUS_DIST"
        optimize "On"