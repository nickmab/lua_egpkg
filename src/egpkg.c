#include "egpkg.h"

#include <mafematikz.h>
#include <sztryng.h>

static const luaL_Reg* pkg_exports[] = {
    &mafematikz_exports,
    &sztryng_exports,
    NULL
};

LUA_EGPKG_API int luaopen_egpkg(lua_State *L) {
    for (int i = 0; pkg_exports[i]; i++) {
        luaL_Reg* mod = pkg_exports[i];
        for (int j = 0; mod[j].name; j++) {
            lua_register(L, mod[j].name, mod[j].func);
        }
    }
    return 1;
}
