#ifndef LUA_EGPKG_SZTRYNG_H
#define LUA_EGPKG_SZTRYNG_H

#include "egpkg.h"

static const char* MODULE_NAME;

static const luaL_Reg sztryng_exports[8];

void sztryng_init(lua_State*);

int sztryng_whatever(lua_State*);

#endif /* LUA_EGPKG_SZTRYNG_H */
