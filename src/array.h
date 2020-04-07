#ifndef LUA_EGPKG_ARRAY_H
#define LUA_EGPKG_ARRAY_H

/* Note that this is adapted from the lua.org tutorial:
   https ://www.lua.org/pil/28.1.html
*/

#include "egpkg.h"

static const char* MODULE_NAME;
static const char* METATABLE_NAME;

static const luaL_Reg array_metamethods[16];

struct Array;
typedef struct Array Array;

void array_init(lua_State*);

static Array* array_from_bottom_of_stack(lua_State*, const char* callerMethodName);
static double* array_get_elem_ptr(lua_State*, const char* callerMethodName);

LAPI_DECL(array_new);
LAPI_DECL(array_set);
LAPI_DECL(array_get);
LAPI_DECL(array_size);
LAPI_DECL(array_countNonZero);
LAPI_DECL(array_tostring);
LAPI_DECL(array_meta_index);
LAPI_DECL(array_meta_newindex);
LAPI_DECL(array_iterator_closure);
LAPI_DECL(array_iterator);

#endif /* LUA_EGPKG_ARRAY_H */
