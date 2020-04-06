#include "egpkg.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <mafematikz.h>
#include <sztryng.h>
#include <stateful.h>

const char* PACKAGE_NAME = "egpkg";

void error(lua_State* L, const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

LUA_EGPKG_API int luaopen_egpkg(lua_State *L) {
    lua_newtable(L);
    stateful_init(L);
    mafematikz_init(L);
    sztryng_init(L);
    lua_setglobal(L, PACKAGE_NAME);
    return 0;
}
