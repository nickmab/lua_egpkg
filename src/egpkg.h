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

#define LAPI_DECL(function_name) static int function_name ## (lua_State* L)

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

const char* PACKAGE_NAME;

void error(lua_State* L, const char* fmt, ...);
void stackDump(lua_State*);

// initialisation function for the package/lib
LUA_EGPKG_API int luaopen_egpkg(lua_State *L);

#endif /* LUA_EGPKG_H */
