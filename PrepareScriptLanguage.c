void PrepareScriptLanguage(){

#ifndef LUA_VERSION_NONE

#ifdef LUA_VERSION_502

LuaState = luaL_newstate();
if (LuaState == NULL) {
printf("Invalid LuaState, shit just got real!\n");
return;
}



luaL_openlibs(LuaState);

#else

#define LUA_OK	0
#define luaL_dofile(LuaState, FileDir) lua_dofile(LuaState, FileDir)
#define lua_pushinteger(LuaState, Value) lua_pushnumber(LuaState, Value)
#define lua_tointeger(LuaState, Index) lua_tonumber(LuaState, Index)
#define lua_createtable(LuaState, ValueOne, ValueTwo) lua_newtable(LuaState)

LuaState = lua_open();

luaopen_base(LuaState);
luaopen_io(LuaState);
luaopen_string(LuaState);
luaopen_math(LuaState);
luaopen_table(LuaState);
//luaopen_package(LuaState);

#endif

#endif
}