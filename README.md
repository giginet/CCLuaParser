# CCLuaParser

This is a utility class for cocos2d-x 3.x Lua-Binding.

## Usage

You must be able to load `CCLuaEngine.h` in your project.

### Execute Function

```lua
function addTwoNumbers(a, b)
    return a + b
end
```

```cpp
// Initialize LuaParser with the script file.
// Each parsers have independent LuaStack.
luaParser::LuaParser * parser = luaParser::LuaParser::create("script.lua");

// Define arguments of the function as cocos2d::LuaValue.
cocos2d::LuaValueArray args = {
    cocos2d::LuaValue::intValue(5), 
    cocos2d::LuaValue::intValue(5)
};

// Call executeFunction(<funcName>, <arguments>, <numberOfReturnValues>);
cocos2d::LuaValueArray returnValues = parser->executeFunction("addTwoNumbers", args, 1);

// You can get return values as LuaValueArray.
// Get the first return value in the following way.
cocos2d::LuaValue returnValue = returnValues.front();

// Print the calc result.
cocos2d::log("answer = %d", returnValue.intValue());
```

### Parse Lua table recursively

WIP
