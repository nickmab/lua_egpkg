#ifndef LUA_EGPKG_ARRAY_H
#define LUA_EGPKG_ARRAY_H

/* Note that this is adapted from the lua.org tutorial:
   https ://www.lua.org/pil/28.1.html
*/

#include "egpkg.h"

static const char* MODULE_NAME;
static const char* METATABLE_NAME;

static const luaL_Reg array_metamethods[8];

struct Array;
typedef struct Array Array;

void array_init(lua_State*);

static Array* array_from_bottom_of_stack(lua_State*, const char* callerMethodName);
static double* array_get_elem_ptr(lua_State*, const char* callerMethodName);

static int array_new(lua_State*);
static int array_set(lua_State*);
static int array_get(lua_State*);
static int array_size(lua_State*);
static int array_countNonZero(lua_State*);
static int array_tostring(lua_State*);
static int array_meta_index(lua_State*);
static int array_meta_newindex(lua_State*);

#endif /* LUA_EGPKG_ARRAY_H */
