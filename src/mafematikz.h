#ifndef LUA_EGPKG_MAFEMATIKZ_H
#define LUA_EGPKG_MAFEMATIKZ_H

#include "egpkg.h"

static const char* MODULE_NAME;

static const luaL_Reg cfunction_exports[8];

void mafematikz_init(lua_State*);

LAPI_DECL(mafematikz_calculayt);
LAPI_DECL(mafematikz_max);

#endif /* LUA_EGPKG_MAFEMATIKZ_H */
