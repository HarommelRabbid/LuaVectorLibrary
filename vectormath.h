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

LUALIB_API int luaL_extendmath(lua_State *L);