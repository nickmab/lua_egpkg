cmake_minimum_required (VERSION 3.15)

Project ("Lua_Egpkg")

if (NOT WIN32)
    message (WARNING "The CMakeLists here have only been tested on windows...")
endif ()

if (MSVC)
    add_compile_options(/MP)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions (LUA_DEBUG)
endif ()

# This we will build ourselves...
set (LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/lua/src")
set (LUA_LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/vendor/lua/src")

add_subdirectory ("vendor/lua")
add_subdirectory ("src")