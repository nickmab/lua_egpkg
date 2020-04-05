#include "egpkg.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <mafematikz.h>
#include <sztryng.h>

const char* PACKAGE_NAME = "egpkg";

void error(lua_State* L, const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

static const luaL_Reg* pkg_exports[] = {
    &mafematikz_exports,
    &sztryng_exports,
    NULL
};

LUA_EGPKG_API int luaopen_egpkg(lua_State *L) {
    lua_newtable(L);
    for (int i = 0; pkg_exports[i]; i++) {
        luaL_Reg* mod = pkg_exports[i];
        for (int j = 0; mod[j].name; j++) {
            lua_pushstring(L, mod[j].name);
            lua_pushcfunction(L, mod[j].func);
            lua_settable(L, -3);
        }
    }
    lua_setglobal(L, PACKAGE_NAME);
    return 0;
}
