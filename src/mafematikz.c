#include "mafematikz.h"

#include <double_vec.hpp>

const luaL_Reg mafematikz_exports[] = {
	{"calculayt", mafematikz_calculayt},
	{NULL, NULL}
};

int mafematikz_calculayt(lua_State* L) {
	double arg1 = luaL_checknumber(L, 1);
	double arg2 = luaL_checknumber(L, 2);
	
	double_vec_t* vec = double_vec_new();
	if (vec == NULL) goto giveup;
	bool errorOut;
	double_vec_push_back(vec, 5.0, &errorOut);
	if (errorOut) goto giveup;
	double_vec_push_back(vec, 6.0, &errorOut);
	if (errorOut) goto giveup;
	double_vec_push_back(vec, -1.0, &errorOut);
	if (errorOut) goto giveup;
	double_vec_push_back(vec, 3.0, &errorOut);
	if (errorOut) goto giveup;

	double maxVal = double_vec_max_value(vec, &errorOut);
	if (errorOut) goto giveup;
	lua_pushnumber(L, maxVal);

	double_vec_delete(vec);
	return 1;

	giveup:
	double_vec_delete(vec);
	lua_pushnumber(L, arg1 - arg2);
	return 1;
}