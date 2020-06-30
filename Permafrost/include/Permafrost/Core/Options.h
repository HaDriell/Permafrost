#pragma once

#include "Permafrost/Core/CommonTypes.h"


class Options
{
public:
    void Clear();
    bool Contains(const std::string& Key) const;

    void Add(const std::string Key, const std::string& Value);
    void Remove(const std::string& Key);

    const std::string&  GetString(const std::string& Key) const;
    
    i32 GetInteger(const std::string& Key) const;
    f32 GetFloat(const std::string& Key) const;

    //Load Argument array
    bool Parse(int argc, char** argv);
    bool Load(const std::string& Filename);
    bool Save(const std::string& Filename);
private:
    std::unordered_map<std::string, std::string> Options;
};