//
//  CCLuaParser.cpp
//  CCLuaParser
//
//  Created by giginet on 5/9/15.
//
//

#include "CCLuaParser.h"
#include "tolua_fix.h"

USING_NS_CC;

NS_LUAPARSER_BEGIN;

LuaParser::LuaParser()
: _stack(nullptr)
{
}

LuaParser::~LuaParser()
{
    CC_SAFE_RELEASE_NULL(_stack);
}

bool LuaParser::init(const char *scriptName)
{
    std::string moduleName = scriptName;
    
    _stack = LuaStack::attach(LuaEngine::getInstance()->getLuaStack()->getLuaState());
    _stack->retain();
    
    if (moduleName.substr(moduleName.length() - 4, moduleName.length()) == ".lua") {
        moduleName.replace(moduleName.end() - 4, moduleName.end(), "");
    }
    _scriptName = moduleName;
    
    this->reload();
    
    return true;
}

LuaParser* LuaParser::create(const char *scriptName)
{
    auto instance = new (std::nothrow) LuaParser();
    if (instance && instance->init(scriptName)) {
        instance->autorelease();
        return instance;
    }
    CC_SAFE_DELETE(instance);
    return nullptr;
}

void LuaParser::reload()
{
    _stack->executeScriptFile(_scriptName.c_str());
    _stack->clean();
}

cocos2d::LuaValue LuaParser::wrapLuaValue(int idx)
{
    auto L = _stack->getLuaState();
    
    if (lua_isboolean(L, idx)) {
        bool value = lua_toboolean(L, idx);
        return LuaValue::booleanValue(value);
    } else if (lua_isnumber(L, idx)) {
        float value = lua_tonumber(L, idx);
        return LuaValue::floatValue(value);
    } else if (lua_isstring(L, idx)) {
        const char* value = lua_tostring(L, idx);
        return LuaValue::stringValue(value);
    } else if (lua_isuserdata(L, idx)) {
        auto obj = static_cast<Ref *>(tolua_tousertype(L, idx, nullptr));
        return LuaValue::ccobjectValue(obj, "");
    }
    assert("Unknown LuaValue");
}

cocos2d::LuaValueArray LuaParser::executeFunction(const char *functionName, cocos2d::LuaValueArray args, int numberOfReturns)
{
    _stack->clean();
    
    auto L = _stack->getLuaState();
    lua_getglobal(L, functionName);
    if (lua_isfunction(L, lua_gettop(L))) {
        for (auto& arg : args) {
            _stack->pushLuaValue(arg);
        }
        
        if (lua_pcall(L, (int)args.size(), numberOfReturns, 0)) {
            log("%s", lua_tostring(L, lua_gettop(L)));
            return LuaValueArray();
        }
    } else {
        return LuaValueArray();
    }
    
    LuaValueArray returns;
    for (int i = 0; i < numberOfReturns; ++i) {
        auto wraped = this->wrapLuaValue(-(numberOfReturns - i));
        returns.push_back(wraped);
    }
    return returns;
}


NS_LUAPARSER_END;