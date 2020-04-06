#include "sztryng.h"

static const char* MODULE_NAME = "sztryng";

static const luaL_Reg cfunction_exports[] = {
	{"whatever", sztryng_whatever},
	{NULL, NULL}
};

void sztryng_init(lua_State* L) {
	const int type = lua_type(L, -1);
	if (type != LUA_TTABLE) {
		error("Initialization error; sztryng_init expected table atop "
			"the stack. Instead got type ID %d.", type);
	}
	// create a table (to nest into the parent table)
	// with name (key) "MODULE_NAME" and value "newtable"
	lua_pushstring(L, MODULE_NAME); // +1 on the stack
	lua_newtable(L);                // +1 on the stack
	// add our own local function definitions to our module's table
	for (int i = 0; cfunction_exports[i].name; i++) {
		lua_pushstring(L, cfunction_exports[i].name); // +1
		lua_pushcfunction(L, cfunction_exports[i].func); // +1
		lua_settable(L, -3); // -2 from the stack
	}
	// now add our module's table to the parent / package one.
	lua_settable(L, -3);
	return 0;
}

int sztryng_whatever(lua_State* L) {
    const char* s = luaL_checkstring(L, 1);
    lua_pushfstring(L, "sztryng says hello: %s", s);
    return 1;
}