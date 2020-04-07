#include "mafematikz.h"

#include <double_vec.hpp>

static const char* MODULE_NAME = "mafematikz";

static const luaL_Reg cfunction_exports[] = {
	{"calculayt", mafematikz_calculayt},
	{"max", mafematikz_max},
	{NULL, NULL}
};

void mafematikz_init(lua_State* L) {
	const int type = lua_type(L, -1);
	if (type != LUA_TTABLE) {
		error("Initialization error; mafematikz_init expected table atop "
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

static int mafematikz_calculayt(lua_State* L) {
	double arg1 = luaL_checknumber(L, 1);
	double arg2 = luaL_checknumber(L, 2);
	lua_pushnumber(L, arg1 - arg2);
	return 1;
}

static int mafematikz_max(lua_State* L) {
	const int numOfArgs = lua_gettop(L);
	if (numOfArgs == 0) {
		lua_pushnil(L);
		return 1;
	}
	
	double_vec_t* vec = double_vec_new();
	if (vec == NULL) {
		error(L, "Unable to malloc double_vec_t in function mafematikz_max");
	}
	
	char errorCode;
	
	for (int i = 1; i <= numOfArgs; i++) {
		double d = luaL_checknumber(L, i);
		double_vec_push_back(vec, d, &errorCode);
		if (errorCode != DOUBLE_VEC_SUCCESS) {
			error(L, "Error code %d operating on double_vec in function mafematikz_max: %s",
				errorCode, errCodeToString(errorCode));
		}
	}

	const double result = double_vec_max_value(vec, &errorCode);
	if (errorCode != DOUBLE_VEC_SUCCESS) {
		error(L, "Error code %d operating on double_vec in function mafematikz_max: %s",
			errorCode, errCodeToString(errorCode));
	}
	lua_pushnumber(L, result);
	return 1;
}