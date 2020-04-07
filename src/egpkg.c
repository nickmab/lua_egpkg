#include "egpkg.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <mafematikz.h>
#include <sztryng.h>
#include <stateful.h>
#include <array.h>

const char* PACKAGE_NAME = "egpkg";

void error(lua_State* L, const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

// Taken from the Lua documentation. Thanks!
// https://www.lua.org/pil/24.2.3.html
void stackDump(lua_State* L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

        case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;

        default:  /* other values */
            printf("%s", lua_typename(L, t));
            break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

LUA_EGPKG_API int luaopen_egpkg(lua_State *L) {
    lua_newtable(L);
    stateful_init(L);
    mafematikz_init(L);
    sztryng_init(L);
    array_init(L);
    lua_setglobal(L, PACKAGE_NAME);
    return 0;
}
