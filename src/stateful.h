#ifndef LUA_EGPKG_STATEFUL_H
#define LUA_EGPKG_STATEFUL_H

#include "egpkg.h"

void stateful_init(lua_State*);
static int staticCounter(lua_State*);
static int newStaticCounter(lua_State*, lua_CFunction target, const char* name);

const luaL_Reg stateful_exports[];

int stateful_statefulA(lua_State*);
int stateful_statefulB(lua_State*);

#endif /* #ifndef LUA_EGPKG_STATEFUL_H */
