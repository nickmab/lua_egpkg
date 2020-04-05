cmake_minimum_required (VERSION 3.15)

set (LIB_NAME lua_egpkg)

file (GLOB_RECURSE PKG_C_SRC "*.c")
file (GLOB_RECURSE PKG_CPP_SRC "*.cpp")

add_library (${LIB_NAME} SHARED ${PKG_CPP_SRC} ${PKG_C_SRC})

target_compile_definitions (${LIB_NAME} PUBLIC LUA_BUILD_AS_DLL)

include_directories(${CMAKE_CURRENT_LIST_DIR} 
                    ${LUA_INCLUDE_DIR})

target_link_libraries(${LIB_NAME} lua_dynamic_lib)

add_executable (lua "${LUA_INCLUDE_DIR}/lua.c")
target_link_libraries(lua lua_dynamic_lib)

add_custom_command(TARGET ${LIB_NAME} 
                   PRE_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${LUA_LIB_DIR}/lua_dynamic_lib.dll" ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET ${LIB_NAME} 
                   PRE_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/egpkg_usage.lua" ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET ${LIB_NAME} 
                   PRE_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_LIST_DIR}/run_example.bat" ${CMAKE_CURRENT_BINARY_DIR})