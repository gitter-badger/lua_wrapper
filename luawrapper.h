/**
*
* @brief LuaWrapper Header
* @author Toni Marquez
*
**/

#ifndef __LUAWRAPPER_H__
#define __LUAWRAPPER_H__ 1

#include <string>
#include "LUA/lua.hpp"

namespace HB {

  class LuaWrapper {

    public:

    /** constructor & destructor **/
    LuaWrapper();
    ~LuaWrapper();

    /// init
    void init(const std::string path);
    /**
    *
    *  this is like the lua stack works (LIFO):
    *
    *       |   |
    *     3 | - | -1
    *     2 | - | -2
    *     1 | - | -3
    *       |___|
    *
    **/

    /**
    * @brief insert global from lua file to the stack and pop it
    * @param const std::string global
    * @return const int / const float / const std::string / const bool
    **/
    const int getGlobalInteger(const std::string global);
    const float getGlobalNumber(const std::string global);
    const std::string getGlobalString(const std::string global);
    const bool getGlobalBoolean(const std::string global);
    /**
    *
    *  integer = 50;
    *
    **/

    /**
    * @brief insert table from lua file to the stack, get a specified field
    *        and pop it
    * @param const std::string table, const std::string field
    * @return const int / const float / const std::string / const bool
    **/
    const int getIntegerFromTable(const std::string table,
                                  const std::string field);
    const float getNumberFromTable(const std::string table,
                                   const std::string field);
    const std::string getStringFromTable(const std::string table,
                                         const std::string field);
    const bool getBooleanFromTable(const std::string table,
                                   const std::string field);
    /**
    *
    *  table = {
    *    integer = 25,
    *    number = 10.5
    *  };
    *
    **/

    /**
    * @brief get an entire array of elements form stack (global array)
    * @param const std::string array
    * @return const int / const float
    **/
    const int* getGlobalArrayOfIntegers(const std::string array,
                                        int* num = NULL);
    const float* getGlobalArrayOfNumbers(const std::string array,
                                         int* num = NULL);
    /**
    *
    *  array = { 1, 2, 3, 4, 5 }; // returns the entire array
    *
    **/

    /**
    * @brief insert table from lua file to the stack and get a specified
    *        position by index
    * @param const std::string array, const short int index
    * @return const int / const float
    **/
    const int getIntegerFromArrayByIndex(const std::string array,
                                         const short int index);
    const float getNumberFromArrayByIndex(const std::string array,
                                          const short int index);
    /**
    *
    *  array = { 1, 2, 3, 4, 5 }; // returns only one element
    *
    **/

    /**
    * @brief get an entire array of elements form stack (table array)
    * @param const std::string array
    * @return const int / const float
    **/
    const int* getArrayOfIntegersFromTable(const std::string table,
                                           const std::string array,
                                           int* num = NULL);
    const float* getArrayOfNumbersFromTable(const std::string table,
                                            const std::string array,
                                            int* num = NULL);
    /**
    *
    *  table = {
    *    array_of_integers = { 1, 2, 3, 4, 5 },
    *    array_of_numbers = { 1.0, 2.0, 3.0, 4.0, 5.0 }
    *  };
    *
    **/

    /// get number of elements of an array
    const int size(const std::string array);
    const int size(const std::string table, const std::string array);

    /// close lua
    void close();

    private:

    /// private vars
    lua_State* LUA_;
  };
}

#endif
