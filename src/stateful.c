#include "stateful.h"

#include <stdio.h>

void stateful_init(lua_State* L) {
	newStaticCounter(L, &staticCounter, "counter");
}

const luaL_Reg stateful_exports[] = {
	{"statefulA", stateful_statefulA},
	{"statefulB", stateful_statefulB},
	{NULL, NULL}
};

static const char* CallCounter = "egpkg_stateful_call_counter";

static int getNextCallCounter(lua_State* L) {
	// first we get the current value of the counter...
	lua_pushlightuserdata(L, CallCounter); // +1 to stack
	lua_gettable(L, LUA_REGISTRYINDEX); // chew 1, add 1 to stack.
	const int type = lua_type(L, -1);
	int counterValue = 0;
	switch (type) {
	case LUA_TNUMBER:
		if (!lua_isinteger(L, -1)) {
			error(L, "CallCounter registry state corrupted; got non-integer: %.1f", 
				lua_tonumber(L, -1));
		}
		counterValue = lua_tointeger(L, -1);
		break;
	case LUA_TNIL: // first time initialization.
		break;
	default:
		error(L, "CallCounter registry state corrupted; got type: %d", type);
	}
	
	// now we increment and update the counter value...
	lua_pushlightuserdata(L, CallCounter); // +1 to stack
	lua_pushinteger(L, ++counterValue); // +1 to stack
	lua_settable(L, LUA_REGISTRYINDEX); // -2 from stack.
	lua_remove(L, -1); // stack was net +1 at this point.
	return counterValue;
}

// to be used as a closure within individual functions - this way we create
// something like a "static" variable with a Lua type, local/private to a single function.
static int staticCounter(lua_State* L) {
	int val = lua_tointeger(L, lua_upvalueindex(1));
	// this is basically our "return value" to be left on the stack.
	lua_pushinteger(L, ++val); // +1 onto the stack
	// this is the value we put back into the upvalue index.
	lua_pushinteger(L, val); // +1 onto the stack
	lua_replace(L, lua_upvalueindex(1)); // -1 from the stack
	return 1;
}

static int newStaticCounter(lua_State* L, lua_CFunction target, const char* name) {
	lua_pushnumber(L, 0); // initialize the counter at zero...
	lua_pushcclosure(L, target, 1); // closure with 1 upvalue
	lua_setglobal(L, name);
	return 0;
}

int stateful_statefulA(lua_State* L) {
	const int globalCallCounter = getNextCallCounter(L);
	lua_pushnumber(L, globalCallCounter);
	return 1;
}

int stateful_statefulB(lua_State* L) {
	const int globalCallCounter = getNextCallCounter(L);
	lua_pushnumber(L, globalCallCounter+(double)7);
	return 1;
}