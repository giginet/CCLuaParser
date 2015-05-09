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
private:
    std::string _scriptName;
    cocos2d::LuaValue wrapLuaValue(int idx);
public:
    static LuaParser * create(const char* scriptName);
    cocos2d::LuaValueArray executeFunction(const char* functionName, cocos2d::LuaValueArray args, int numberOfReturns);
    
    void reload();
    /// Lua Stack
    CC_SYNTHESIZE_READONLY(cocos2d::LuaStack *, _stack, Stack);
};

NS_LUAPARSER_END;

#endif /* defined(__CCLuaParser__CCLuaParser__) */
