workspace "Sirius"
    architecture "x64"
    location "build"
    configurations { "Debug", "Release", "Distribution" }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    multiprocessorcompile "On"

function CommonSettings()
    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    filter "system:windows"
        defines { "SIRIUS_PLATFORM_WINDOWS" }
    filter "system:linux"
        defines { "SIRIUS_PLATFORM_LINUX" }
        buildoptions { "-fvisibility=hidden" }

    filter "configurations:Debug"
        defines "SIRIUS_DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "SIRIUS_RELEASE"
        optimize "On"
    filter "configurations:Distribution"
        defines "SIRIUS_DIST"
        optimize "On"
    filter {} 
end

function CopyDynamicLib()
    filter "system:windows"
        postbuildcommands {
            "copy /Y \"%{cfg.buildtarget.relpath}\" \"..\\build\\\""
        }

    filter "system:linux"
        postbuildcommands {
            "cp -f \"%{cfg.buildtarget.relpath}\" \"../build/\""
        }
    filter {}
end

project "Sirius"
    kind "SharedLib"
    language "C++"
    
    targetdir ("build/binaries/" .. outputdir .. "/%{prj.name}")
    objdir    ("build/intermediate/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/include/**.h", "%{prj.name}/source/**.h", "%{prj.name}/source/**.cpp" }
    includedirs { "%{prj.name}/third-party/spdlog/include", "%{prj.name}/include" }
    
    defines "SIRIUS_BUILD_DLL"
    CopyDynamicLib()
    
    CommonSettings()

project "Sandbox"    
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("build")
    objdir    ("build/intermediate/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/include/**.h", "%{prj.name}/include/**.cpp", "%{prj.name}/source/**.h", "%{prj.name}/source/**.cpp" }
    includedirs { "Sirius/third-party/spdlog/include", "%{prj.name}/include", "Sirius/include" }
    
    links { "Sirius" }
    
    filter "system:linux"
        linkoptions { "-Wl,-rpath,'$ORIGIN'" }
    filter {}

    CommonSettings()