#include "array.h"

#include <double_vec.hpp>

static const char* MODULE_NAME = "array";
static const char* METATABLE_NAME = "egpkg_array";

static const luaL_Reg array_metamethods[] = {
    {"__tostring", array_tostring},
    {"__index", array_meta_index},
    {"__newindex", array_meta_newindex},
    {"set", array_set},
    {"get", array_get},
    {"size", array_size},
    {"countNonZero", array_countNonZero},
    {"iter", array_iterator_closure},
	{NULL, NULL}
};

void array_init(lua_State* L) {
    // create a table (to nest into the parent table)
    // with name (key) "MODULE_NAME" and value "newtable"
    lua_pushstring(L, MODULE_NAME); // +1 on the stack
    lua_newtable(L);                // +1 on the stack
    // attach the "new" function within our own module table
    lua_pushstring(L, "new");
    lua_pushcfunction(L, array_new);
    lua_settable(L, -3);
    // attach our own module table to the parent package table.
    lua_settable(L, -3);
    // OK, so up to here, we are "stack neutral". 

    luaL_newmetatable(L, METATABLE_NAME);

    // now attach the desired methods to the metatable
    for (int i = 0; array_metamethods[i].name; i++) {
        lua_pushstring(L, array_metamethods[i].name);
        lua_pushcfunction(L, array_metamethods[i].func);
        lua_settable(L, -3);
    }

    // now our metatable is left on top of the stack, but we
    // don't actually need to do anything with it.
    lua_remove(L, -1);
    return 0;
}

struct Array {
    int size;
    double values[1]; // note that size 1 is a placeholder.
};

static Array* array_from_bottom_of_stack(
    lua_State* L, const char* callerMethodName) {
    void* ud = luaL_checkudata(L, 1, METATABLE_NAME);
    if (ud != NULL) {
        return (Array*)ud;
    }
    else {
        error(L, "Error in %s.%s calling array:%s. Receiver is not an array!",
            PACKAGE_NAME, MODULE_NAME, callerMethodName);
    }
}

// Checks arg 1 on the stack is indeed an Array userdata.
// Assumes arg 2 on the stack is the desired int index.
// Checks validity of index - must be in range [1:size].
// Returns ptr to the array element we're looking to read/modify.
static double* array_get_elem_ptr(
    lua_State* L, const char* callerMethodName) {
    Array* a = array_from_bottom_of_stack(L, callerMethodName);
    const int idx = luaL_checkinteger(L, 2);

    if (idx < 1 || idx > a->size) {
        error(L, "Error in %s.%s calling array:%s. Array index %d out "
            "of range. Must be between 1 and %d.",
            PACKAGE_NAME, MODULE_NAME, callerMethodName, idx, a->size);
    }
    return &a->values[idx-1];
}

static int array_new(lua_State* L) {
    // to initialize an array of 'n' elements...
    const int n = luaL_checkinteger(L, 1);
    
    // the Array itself already has space/size of 1 element,
    // hence we have (n-1) term below for remaining values.
    size_t nbytes = sizeof(Array) + (n-1) * sizeof(double);
    
    // this will also be sitting on top of the stack now...
    Array* a = (Array*)lua_newuserdata(L, nbytes);
    // find the metatable to be associated with this userdatum
    luaL_getmetatable(L, METATABLE_NAME); // puts it on the stack
    // set that metatable on our userdatum
    lua_setmetatable(L, -2); // chews it from the stack
    
    // 'zero' the values (is this actually necessary? 
    // the original example/code did not have this step.
    for (int i = 0; i < n; i++) a->values[i] = 0;
    a->size = n;
    return 1;
}

static int array_set(lua_State* L) {
    static const char* METHOD_NAME = "set";
    *array_get_elem_ptr(L, METHOD_NAME) = luaL_checknumber(L, 3);
    return 0;
}

static int array_get(lua_State* L) {
    static const char* METHOD_NAME = "get";
    lua_pushnumber(L, *array_get_elem_ptr(L, METHOD_NAME));
    return 1;
}

static int array_size(lua_State* L) {
    static const char* METHOD_NAME = "size";
    Array* a = array_from_bottom_of_stack(L, METHOD_NAME);
    lua_pushinteger(L, a->size);
    return 1;
}

static int array_countNonZero(lua_State* L) {
    static const char* METHOD_NAME = "countNonZero";
    Array* a = array_from_bottom_of_stack(L, METHOD_NAME);
    int count = 0;
    for (int i = 0; i < a->size; i++) {
        if (a->values[i] != 0.0) count++;
    }
    lua_pushinteger(L, count);
    return 1;
}

static int array_tostring(lua_State* L) {
    static const char* METHOD_NAME = "__tostring";
    Array* a = array_from_bottom_of_stack(L, METHOD_NAME);
    lua_pushfstring(L, "%s.%s.array(%d)", 
        PACKAGE_NAME, MODULE_NAME, a->size);
    return 1;
}

static int array_meta_index(lua_State* L) {
    const int type = lua_type(L, 2);
    switch (type) {
    case LUA_TNUMBER:
        return array_get(L);
    default:
        luaL_getmetatable(L, METATABLE_NAME); // puts it on the stack
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
        lua_remove(L, -2); // get the metatable off the stack
        return 1; // leave the result on the stack
    }
}

static int array_meta_newindex(lua_State* L) {
    const int type = lua_type(L, 2);
    switch (type) {
    case LUA_TNUMBER:
        return array_set(L);
    default:
        luaL_getmetatable(L, METATABLE_NAME); // puts it on the stack
        lua_pushvalue(L, 2);
        lua_pushvalue(L, 3);
        lua_settable(L, -3);
        lua_settop(L, -1); // get it (the metatable) off the stack.
        return 0;
    }
}

// provides functionality basically identical to ipairs(a) for the array
static int array_iterator_closure(lua_State* L) {
    array_size(L);
    // closure with 1 upvalue: the loop max count.
    // note that the initial upvalue - the size of the array - 
    // will already be on top of the stack, ready to get chewed here...
    lua_pushcclosure(L, &array_iterator, 1); 
    // new closure is left on the stack.
    lua_pushvalue(L, 1); // this is the array user data
    lua_pushinteger(L, 0); // the initial loop index/counter
    return 3; 
}

static int array_iterator(lua_State* L) {
    const int arraySize = lua_tointeger(L, lua_upvalueindex(1));
    int idx = luaL_checkinteger(L, 2);
    lua_remove(L, 2); // now we've read the int, we can burn it.
    if (idx++ == arraySize) {
        lua_pushnil(L);
        return 1;
    }
    else
    {
        lua_pushinteger(L, idx); // once for the return value...
        lua_pushinteger(L, idx); // and once as arg for get function...
        array_get(L); // chews arg, replaces with 'gotten' value
        return 2;
    }
}