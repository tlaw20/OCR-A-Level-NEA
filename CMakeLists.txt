cmake_minimum_required(VERSION 3.15)
project(BoxGame C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On Windows, build the C/C++ runtime into the .exe so it runs on any PC
# without needing extra installs.
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
endif()

# Only build the raylib library itself, and link it into the .exe
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Download raylib automatically (pinned to version 5.5)
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)
FetchContent_MakeAvailable(raylib)

add_executable(BoxGame main.cpp)
target_link_libraries(BoxGame PRIVATE raylib)

# Open as a normal window, with no black console window behind it.
# (Delete this block if you want the console back for debugging.)
if (MSVC)
    target_link_options(BoxGame PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()
