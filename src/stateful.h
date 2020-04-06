#ifndef LUA_EGPKG_STATEFUL_H
#define LUA_EGPKG_STATEFUL_H

#include "egpkg.h"

static const char* MODULE_NAME;

static const char* CallCounter;

void stateful_init(lua_State*);
static int newStaticCounter(lua_State*, lua_CFunction target);

int stateful_statefulA(lua_State*);
int stateful_statefulB(lua_State*);

#endif /* #ifndef LUA_EGPKG_STATEFUL_H */
