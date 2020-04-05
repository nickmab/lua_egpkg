#ifndef LUA_EGPKG_H
#define LUA_EGPKG_H

// macro to prefix all exported api functions
#ifndef LUA_EGPKG_API
    #ifdef _WIN32
        #define LUA_EGPKG_API __declspec(dllexport)
    #else
        #define LUA_EGPKG_API __attribute__ ((visibility ("default")))
    #endif
#endif

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

const char* PACKAGE_NAME;

// initialisation function for the package/lib
LUA_EGPKG_API int luaopen_egpkg(lua_State *L);

#endif /* LUA_EGPKG_H */
