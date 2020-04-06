#ifndef LUA_EGPKG_MAFEMATIKZ_H
#define LUA_EGPKG_MAFEMATIKZ_H

#include "egpkg.h"

static const char* MODULE_NAME;

static const luaL_Reg cfunction_exports[8];

void mafematikz_init(lua_State*);

int mafematikz_calculayt(lua_State*);
int mafematikz_max(lua_State*);

#endif /* LUA_EGPKG_MAFEMATIKZ_H */
