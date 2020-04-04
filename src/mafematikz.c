#include "mafematikz.h"

const luaL_Reg mafematikz_exports[] = {
	{"calculayt", mafematikz_calculayt},
	{NULL, NULL}
};

int mafematikz_calculayt(lua_State* L) {
	double arg1 = luaL_checknumber(L, 1);
	double arg2 = luaL_checknumber(L, 2);
	lua_pushnumber(L, arg1 - arg2);
	return 1;
}