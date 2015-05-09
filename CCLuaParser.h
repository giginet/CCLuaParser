//
//  CCLuaParser.h
//  CCLuaParser
//
//  Created by giginet on 5/9/15.
//
//

#ifndef __CCLuaParser__CCLuaParser__
#define __CCLuaParser__CCLuaParser__


#include "cocos2d.h"
#include "CCLuaEngine.h"

#define NS_LUAPARSER_BEGIN namespace luaParser {
#define NS_LUAPARSER_END }
// #define std::vector<cocos2d::LuaValueType> TypeArray

NS_LUAPARSER_BEGIN;

class LuaParser :public cocos2d::Ref {
CC_CONSTRUCTOR_ACCESS:
    LuaParser();
    virtual ~LuaParser();
    bool init(const char* scriptName);
    
protected:
    cocos2d::LuaValue wrapLuaValue(lua_State* L, int idx);
public:
    static LuaParser * create(const char* scriptName);
    cocos2d::LuaValueArray executeFunction(const char* functionName, cocos2d::LuaValueArray args);
    cocos2d::LuaValueArray executeFunction(lua_State* L, int idx, cocos2d::LuaValueArray args);
};

NS_LUAPARSER_END;

#endif /* defined(__CCLuaParser__CCLuaParser__) */
