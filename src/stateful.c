#include "stateful.h"

#include <stdio.h>

static const char* MODULE_NAME = "stateful";

static const char* CallCounter = "egpkg_stateful_call_counter";

void stateful_init(lua_State* L) {
	const int type = lua_type(L, -1);
	if (type != LUA_TTABLE) {
		error("Initialization error; stateful_init expected table atop "
			"the stack. Instead got type ID %d.", type);
	}
	// create a table (to nest into the parent table)
	// with name (key) "MODULE_NAME" and value "newtable"
	lua_pushstring(L, MODULE_NAME); // +1 on the stack
	lua_newtable(L);                // +1 on the stack
	
	// add our own local function definitions to our module's table
	lua_pushstring(L, "statefulA"); // closure name/key in our table...
	newStaticCounter(L, &stateful_statefulA);
	lua_settable(L, -3); // -2 from the stack
	
	// add our own local function definitions to our module's table
	lua_pushstring(L, "statefulB"); // closure name/key in our table...
	newStaticCounter(L, &stateful_statefulB);
	lua_settable(L, -3); // -2 from the stack

	// now add our module's table to the parent / package one.
	lua_settable(L, -3);
}

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

#define GET_AND_INCR_STATIC_COUNT(variable_name) \
	int variable_name = lua_tointeger(L, lua_upvalueindex(1)); \
	/* this is basically our "return value" to be left on the stack. */ \
	lua_pushinteger(L, ++ ## variable_name); /* +1 onto the stack */ \
	lua_replace(L, lua_upvalueindex(1)); /* -1 from the stack */

static int newStaticCounter(lua_State* L, lua_CFunction target) {
	lua_pushnumber(L, 0); // initialize the counter at zero...
	lua_pushcclosure(L, target, 1); // closure with 1 upvalue
	return 1; // new closure is left on the stack.
}

static int stateful_statefulA(lua_State* L) {
	const int globalCallCounter = getNextCallCounter(L);
	GET_AND_INCR_STATIC_COUNT(localCallCounter);
	lua_pushnumber(L, globalCallCounter);
	lua_pushnumber(L, localCallCounter);
	return 2;
}

static int stateful_statefulB(lua_State* L) {
	const int globalCallCounter = getNextCallCounter(L);
	GET_AND_INCR_STATIC_COUNT(localCallCounter);
	char buf[64];
	sprintf(buf, "statefulB; global call count is %d and local is %d.\0", 
		globalCallCounter, localCallCounter);
	lua_pushstring(L, buf);
	return 1;
}

#undef GET_AND_INCR_STATIC_COUNT