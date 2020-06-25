#pragma once

#include "Permafrost/Core/Action.h"
#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Delegate.h"

class ActionMap
{
public:
    void Add(const std::string& Name);
    void Remove(const std::string& Name);

    Action* GetAction(const std::string& Name);
     
private:
    std::unordered_map<std::string, Action> Actions;
};