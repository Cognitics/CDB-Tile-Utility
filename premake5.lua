
workspace "cdbgen"
    configurations { "Debug", "Release" }
    location "build"

    filter "system:Windows"
        system "windows"
        defines { "WIN32" }

project "cdbgen"
    location "build/cdbgen"
    kind "ConsoleApp"
    language "C++"
    architecture "x86_64"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { ".", "../include", "c:/boost_1_67_0/include", "c:/svn/ext/gdal213/vc14/x64/include" }
    files { "premake5.lua", "src/**.h", "src/**.cpp" }
    libdirs { "c:/boost_1_67_0/lib/vc141", "c:/svn/ext/gdal213/vc14/x64/lib" }
    links { "gdal_i" }
    defines { }
    filter "configurations:Debug"
        defines { "DEBUG" }
        links { "libboost_filesystem-vc141-mt-gd-x64-1_67" }
        symbols "On"
    filter "configurations:Release"
        defines { "NDEBUG" }
        links { "libboost_filesystem-vc141-mt-x64-1_67" }
        optimize "On"




