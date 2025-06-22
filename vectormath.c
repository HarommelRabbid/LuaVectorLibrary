/*
    Lua vector library by Harommel OddSock
    Extends the math library
    Lua 5.1+
    If in Lua 5.2+, compile your Lua with -DLUA_COMPAT_MODULE
    Licensed under the GPLv3 license
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct {
    float x;
    float y;
} vector2f;

typedef struct {
    float x;
    float y;
    float z;
} vector3f;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vector4f;

// ------------------------ 2 coord vectors ------------------------
static int lua_vector2(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));

    v2->x = luaL_checknumber(L, 1);
    v2->y = luaL_checknumber(L, 2);

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2table(lua_State *L){
    vector2f *v2 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    lua_newtable(L);
    lua_pushnumber(L, v2->x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, v2->y); lua_setfield(L, -2, "y");
    return 1;
}

static int lua_v2x(lua_State *L){
    vector2f *v2 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    lua_pushnumber(L, v2->x);
    return 1;
}

static int lua_v2y(lua_State *L){
    vector2f *v2 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    lua_pushnumber(L, v2->y);
    return 1;
}

static int lua_v2add(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x + v22->x;
    v2->y = v21->y + v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2sub(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x - v22->x;
    v2->y = v21->y - v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2mul(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x * v22->x;
    v2->y = v21->y * v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2div(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x / v22->x;
    v2->y = v21->y / v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2mod(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x % v22->x;
    v2->y = v21->y % v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2pow(lua_State *L){
    vector2f *v2 = (vector2f *)lua_newuserdata(L, sizeof(vector2f));
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v22 = (vector2f *)luaL_checkudata(L, 2, "vector2");
    v2->x = v21->x ^ v22->x;
    v2->y = v21->y ^ v22->y;

    luaL_getmetatable(L, "vector2");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v2eq(lua_State *L){
    vector2f *v2 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    vector2f *v21 = (vector2f *)luaL_checkudata(L, 2, "vector2");

    lua_pushboolean(L, (v2->x == v21->x) && (v2->y == v21->y));
    return 1;
}

static int lua_v2len(lua_State *L){
    vector2f *v2 = (vector2f *)luaL_checkudata(L, 1, "vector2");
    lua_pushnumber(L, sqrtf(v2->x * v2->x + v2->y * v2->y));
    return 1;
}

static const luaL_Reg v2_methods[] = {
    {"x", lua_v2x},
    {"y", lua_v2y},
    {"table", lua_v2table},
    {"__add", lua_v2add},
    {"__sub", lua_v2sub},
    {"__mul", lua_v2mul},
    {"__div", lua_v2div},
    {"__mod", lua_v2mod},
    {"__pow", lua_v2pow},
    {"__eq", lua_v2eq},
    {"__len", lua_v2len},
    {NULL, NULL}
};

// ------------------------ 3 coord vectors ------------------------
static int lua_vector3(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));

    v3->x = luaL_checknumber(L, 1);
    v3->y = luaL_checknumber(L, 2);
    v3->z = luaL_checknumber(L, 3);

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3table(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    lua_newtable(L);
    lua_pushnumber(L, v3->x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, v3->y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, v3->z); lua_setfield(L, -2, "z");
    return 1;
}

static int lua_v3x(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    lua_pushnumber(L, v3->x);
    return 1;
}

static int lua_v3y(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    lua_pushnumber(L, v3->y);
    return 1;
}

static int lua_v3z(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    lua_pushnumber(L, v3->z);
    return 1;
}

static int lua_v3add(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x + v32->x;
    v3->y = v31->y + v32->y;
    v3->z = v31->z + v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3sub(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x - v32->x;
    v3->y = v31->y - v32->y;
    v3->z = v31->z - v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3mul(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x * v32->x;
    v3->y = v31->y * v32->y;
    v3->z = v31->z * v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3div(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x / v32->x;
    v3->y = v31->y / v32->y;
    v3->z = v31->z / v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3mod(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x % v32->x;
    v3->y = v31->y % v32->y;
    v3->z = v31->z % v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3pow(lua_State *L){
    vector3f *v3 = (vector3f *)lua_newuserdata(L, sizeof(vector3f));
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v32 = (vector3f *)luaL_checkudata(L, 2, "vector3");
    v3->x = v31->x ^ v32->x;
    v3->y = v31->y ^ v32->y;
    v3->z = v31->z ^ v32->z;

    luaL_getmetatable(L, "vector3");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v3eq(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    vector3f *v31 = (vector3f *)luaL_checkudata(L, 2, "vector3");

    lua_pushboolean(L, (v3->x == v31->x) && (v3->y == v31->y) && (v3->z == v31->z));
    return 1;
}

static int lua_v3len(lua_State *L){
    vector3f *v3 = (vector3f *)luaL_checkudata(L, 1, "vector3");
    lua_pushnumber(L, sqrtf(v3->x * v3->x + v3->y * v3->y + v3->z * v3->z));
    return 1;
}

static const luaL_Reg v3_methods[] = {
    {"x", lua_v3x},
    {"y", lua_v3y},
    {"z", lua_v3z},
    {"table", lua_v3table},
    {"__add", lua_v3add},
    {"__sub", lua_v3sub},
    {"__mul", lua_v3mul},
    {"__div", lua_v3div},
    {"__mod", lua_v3mod},
    {"__pow", lua_v3pow},
    {"__eq", lua_v3eq},
    {"__len", lua_v3len},
    {NULL, NULL}
};

// ------------------------ 4 coord vectors ------------------------
static int lua_vector4(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));

    v4->x = luaL_checknumber(L, 1);
    v4->y = luaL_checknumber(L, 2);
    v4->z = luaL_checknumber(L, 3);
    v4->w = luaL_checknumber(L, 4);

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4table(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_newtable(L);
    lua_pushnumber(L, v4->x); lua_setfield(L, -2, "x");
    lua_pushnumber(L, v4->y); lua_setfield(L, -2, "y");
    lua_pushnumber(L, v4->z); lua_setfield(L, -2, "z");
    lua_pushnumber(L, v4->w); lua_setfield(L, -2, "w");
    return 1;
}

static int lua_v4x(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_pushnumber(L, v4->x);
    return 1;
}

static int lua_v4y(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_pushnumber(L, v4->y);
    return 1;
}

static int lua_v4z(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_pushnumber(L, v4->z);
    return 1;
}

static int lua_v4w(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_pushnumber(L, v4->w);
    return 1;
}

static int lua_v4add(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x + v42->x;
    v4->y = v41->y + v42->y;
    v4->z = v41->z + v42->z;
    v4->w = v41->w + v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4sub(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x - v42->x;
    v4->y = v41->y - v42->y;
    v4->z = v41->z - v42->z;
    v4->w = v41->w - v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4mul(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x * v42->x;
    v4->y = v41->y * v42->y;
    v4->z = v41->z * v42->z;
    v4->w = v41->w * v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4div(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x / v42->x;
    v4->y = v41->y / v42->y;
    v4->z = v41->z / v42->z;
    v4->w = v41->w / v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4mod(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x % v42->x;
    v4->y = v41->y % v42->y;
    v4->z = v41->z % v42->z;
    v4->w = v41->w % v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4pow(lua_State *L){
    vector4f *v4 = (vector4f *)lua_newuserdata(L, sizeof(vector4f));
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v42 = (vector4f *)luaL_checkudata(L, 2, "vector4");
    v4->x = v41->x ^ v42->x;
    v4->y = v41->y ^ v42->y;
    v4->z = v41->z ^ v42->z;
    v4->w = v41->w ^ v42->w;

    luaL_getmetatable(L, "vector4");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_v4eq(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    vector4f *v41 = (vector4f *)luaL_checkudata(L, 2, "vector4");

    lua_pushboolean(L, (v4->x == v41->x) && (v4->y == v41->y) && (v4->z == v41->z) && (v4->w == v41->w));
    return 1;
}

static int lua_v4len(lua_State *L){
    vector4f *v4 = (vector4f *)luaL_checkudata(L, 1, "vector4");
    lua_pushnumber(L, sqrtf(v4->x * v4->x + v4->y * v4->y + v4->z * v4->z + v4->w * v4->w));
    return 1;
}

static const luaL_Reg v4_methods[] = {
    {"x", lua_v4x},
    {"y", lua_v4y},
    {"z", lua_v4z},
    {"w", lua_v4w},
    {"table", lua_v4table},
    {"__add", lua_v4add},
    {"__sub", lua_v4sub},
    {"__mul", lua_v4mul},
    {"__div", lua_v4div},
    {"__mod", lua_v4mod},
    {"__pow", lua_v4pow},
    {"__eq", lua_v4eq},
    {"__len", lua_v4len},
    {NULL, NULL}
};


static const luaL_Reg math_lib[] = {
	{"vector2", lua_vector2},
    {"vector3", lua_vector3},
    {"vector4", lua_vector4},
    {NULL, NULL}
};

LUALIB_API int luaL_extendmath(lua_State *L){
    luaL_newmetatable(L, "vector2");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    luaL_register(L, NULL, v2_methods);

    luaL_newmetatable(L, "vector3");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    luaL_register(L, NULL, v3_methods);

    luaL_newmetatable(L, "vector4");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    luaL_register(L, NULL, v4_methods);

    luaL_register(L, "math", math_lib);
}