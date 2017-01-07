/**
*
* @brief LuaWrapper Class
* @author Toni Marquez
*
**/

#include <windows.h>
#include "hotbyte/log.h"
#include "hotbyte/luawrapper.h"

namespace HB {

  /// constructor
  LuaWrapper::LuaWrapper()
    : LUA_(nullptr) {}

  /// init
  void LuaWrapper::init(const std::string path) {

    LUA_ = luaL_newstate();
    luaL_openlibs(LUA_);
    if (luaL_dofile(LUA_, path.c_str())) {
      std::string error;
      std::string file = __FILE__;
      std::string line = std::to_string(__LINE__);
      error = "ERROR LOADING LUA";
      Log log;
      log.dump(file, line, error);
      exit(EXIT_FAILURE);
    }
  }

  /**
  * @brief insert global from lua file to the stack and pop it
  * @param const std::string global
  * @return const int / const float / const std::string / const bool
  **/
  const int LuaWrapper::getGlobalInteger(const std::string global) {

    lua_getglobal(LUA_, global.c_str());
    int integer = lua_tointeger(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return integer;
  }

  const float LuaWrapper::getGlobalNumber(const std::string global) {

    lua_getglobal(LUA_, global.c_str());
    float number = lua_tonumber(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return number;
  }

  const std::string LuaWrapper::getGlobalString(const std::string global) {

    lua_getglobal(LUA_, global.c_str());
    std::string string = (std::string)lua_tostring(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return string;
  }

  const bool LuaWrapper::getGlobalBoolean(const std::string global) {

    lua_getglobal(LUA_, global.c_str());
    bool boolean = lua_toboolean(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return boolean;
  }

  /**
  * @brief insert table from lua file to the stack, get a specified field
  *        and pop it
  * @param const std::string table, const std::string field
  * @return const int / const float / const std::string / const bool
  **/
  const int LuaWrapper::getIntegerFromTable(const std::string table,
                                            const std::string field) {

    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, field.c_str());
    int integer = lua_tointeger(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return integer;
  }

  const float LuaWrapper::getNumberFromTable(const std::string table,
                                             const std::string field) {

    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, field.c_str());
    double number = lua_tonumber(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return number;
  }

  const std::string LuaWrapper::getStringFromTable(const std::string table,
                                                   const std::string field) {

    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, field.c_str());
    std::string string = (std::string)lua_tostring(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return string;
  }

  const bool LuaWrapper::getBooleanFromTable(const std::string table,
                                             const std::string field) {

    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, field.c_str());
    bool boolean = lua_toboolean(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return boolean;
  }

  /**
  * @brief get an entire array of elements form stack (global array)
  * @param const std::string array
  * @return const int / const float
  **/
  const int* LuaWrapper::getGlobalArrayOfIntegers(const std::string array,
                                                  int* num) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    if (num!=NULL) { *num = num_elements; }
    int* integer_array = new int[num_elements];
    for (unsigned short int i = 0; i < num_elements; i++) {
      lua_checkstack(LUA_, 3);
      lua_getglobal(LUA_, array.c_str());
      lua_pushinteger(LUA_, i+1);
      lua_gettable(LUA_, -2);
      integer_array[i] = lua_tointeger(LUA_, -1);
      lua_pop(LUA_, lua_gettop(LUA_));
    }
    return integer_array;
  }

  const float* LuaWrapper::getGlobalArrayOfNumbers(const std::string array,
                                                   int* num) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    if (num!=NULL) { *num = num_elements; }
    float* number_array = new float[num_elements];
    for (unsigned short int i = 0; i < num_elements; i++) {
      lua_checkstack(LUA_, 3);
      lua_getglobal(LUA_, array.c_str());
      lua_pushnumber(LUA_, i+1);
      lua_gettable(LUA_, -2);
      number_array[i] = lua_tonumber(LUA_, -1);
      lua_pop(LUA_, lua_gettop(LUA_));
    }
    return number_array;
  }

  /**
  * @brief insert table from lua file to the stack and get a specified
  *        position by index
  * @param const std::string array, const short int index
  * @return const int / const float / const std::string / const bool
  **/
  const int LuaWrapper::getIntegerFromArrayByIndex(const std::string array,
                                                   const short int index) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, array.c_str());
    lua_pushinteger(LUA_, index+1);
    lua_gettable(LUA_, -2);
    int integer = lua_tointeger(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return integer;
  }

  const float LuaWrapper::getNumberFromArrayByIndex(const std::string array,
                                                    const short int index) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, array.c_str());
    lua_pushnumber(LUA_, index+1);
    lua_gettable(LUA_, -2);
    float number = lua_tonumber(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return number;
  }

  /**
  * @brief get an entire array of elements form stack (table array)
  * @param const std::string array
  * @return const int / const float
  **/
  const int* LuaWrapper::getArrayOfIntegersFromTable(const std::string table,
                                                     const std::string array,
                                                     int* num) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    if (num!=NULL) { *num = num_elements; }
    int* integer_array = new int[num_elements];
    for (unsigned short int i = 0; i < num_elements; i++) {
      lua_checkstack(LUA_, 3);
      lua_getglobal(LUA_, table.c_str());
      lua_getfield(LUA_, -1, array.c_str());
      lua_pushinteger(LUA_, i+1);
      lua_gettable(LUA_, -2);
      integer_array[i] = lua_tointeger(LUA_, -1);
      lua_pop(LUA_, lua_gettop(LUA_));
    }
    return integer_array;
  }

  const float* LuaWrapper::getArrayOfNumbersFromTable(const std::string table,
                                                      const std::string array,
                                                      int* num) {

    lua_checkstack(LUA_, 3);
    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    if (num!=NULL) { *num = num_elements; }
    float* number_array = new float[num_elements];
    for (unsigned short int i = 0; i < num_elements; i++) {
      lua_checkstack(LUA_, 3);
      lua_getglobal(LUA_, table.c_str());
      lua_getfield(LUA_, -1, array.c_str());
      lua_pushinteger(LUA_, i+1);
      lua_gettable(LUA_, -2);
      number_array[i] = lua_tonumber(LUA_, -1);
      lua_pop(LUA_, lua_gettop(LUA_));
    }
    return number_array;
  }

  /// get number of elements of an array
  const int LuaWrapper::size(const std::string array) {

    lua_getglobal(LUA_, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return num_elements;
  }

  const int LuaWrapper::size(const std::string table, const std::string array) {

    lua_getglobal(LUA_, table.c_str());
    lua_getfield(LUA_, -1, array.c_str());
    int num_elements = luaL_len(LUA_, -1);
    lua_pop(LUA_, lua_gettop(LUA_));
    return num_elements;
  }

  /// close lua
  void LuaWrapper::close() {
    lua_close(LUA_);
  }

  /// destructor
  LuaWrapper::~LuaWrapper() {

    close();
    LUA_ = nullptr;
  }
}
