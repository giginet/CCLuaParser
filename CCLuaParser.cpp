//
//  CCLuaParser.cpp
//  Hopper
//
//  Created by giginet on 5/9/15.
//
//

#include "CCLuaParser.h"

NS_LUAPARSER_BEGIN;

LuaParser::LuaParser()
{
}

LuaParser::~LuaParser()
{
}

bool LuaParser::init(const char *scriptName)
{
    return true;
}

LuaParser* LuaParser::create(const char *scriptName)
{
    auto instance = new LuaParser();
    if (instance && instance->init(scriptName)) {
        instance->autorelease();
        return instance;
    }
    CC_SAFE_DELETE(instance);
    return nullptr;
}

cocos2d::LuaValue wrapLuaValue(lua_State *L, int idx)
{
    if (lua_isboolean(L, idx)) {
        bool value = lua_toboolean(L, idx);
        return cocos2d::LuaValue::booleanValue(value);
    }
}

cocos2d::LuaValueArray LuaParser::executeFunction(const char *functionName, cocos2d::LuaValueArray args)
{
}

cocos2d::LuaValueArray LuaParser::executeFunction(lua_State *L, int idx, cocos2d::LuaValueArray args)
{
}

NS_LUAPARSER_END;