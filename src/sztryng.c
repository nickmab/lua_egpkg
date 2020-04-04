#include "sztryng.h"

const luaL_Reg sztryng_exports[] = {
	{"whatever", sztryng_whatever},
	{NULL, NULL}
};

int sztryng_whatever(lua_State* L) {
    const char* s = luaL_checkstring(L, 1);
    lua_pushfstring(L, "sztryng says hello: %s", s);
    return 1;
}