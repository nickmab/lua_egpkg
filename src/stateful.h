#ifndef LUA_EGPKG_STATEFUL_H
#define LUA_EGPKG_STATEFUL_H

#include "egpkg.h"

static const char* MODULE_NAME;

static const char* CallCounter;

void stateful_init(lua_State*);
static int newStaticCounter(lua_State*, lua_CFunction target);

LAPI_DECL(stateful_statefulA);
LAPI_DECL(stateful_statefulB);

#endif /* #ifndef LUA_EGPKG_STATEFUL_H */
