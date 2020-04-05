#include "mafematikz.h"

#include <double_vec.hpp>

const luaL_Reg mafematikz_exports[] = {
	{"calculayt", mafematikz_calculayt},
	{"max", mafematikz_max},
	{NULL, NULL}
};

int mafematikz_calculayt(lua_State* L) {
	double arg1 = luaL_checknumber(L, 1);
	double arg2 = luaL_checknumber(L, 2);
	lua_pushnumber(L, arg1 - arg2);
	return 1;
}

int mafematikz_max(lua_State* L) {
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