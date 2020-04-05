#include "egpkg.h"

#include <mafematikz.h>
#include <sztryng.h>

const char* PACKAGE_NAME = "egpkg";

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
