#include "Permafrost/Core/ActionMap.h"
#include "Permafrost/Core/Log.h"

void ActionMap::Add(const std::string& Name)
{
    Actions[Name]; // Initializes & Emplaces a new Pair [Name, Action()]
}

void ActionMap::Remove(const std::string& Name)
{
    auto It = Actions.find(Name);
    if (It != Actions.end())
    {
        Actions.erase(It);
    }
}

Action* ActionMap::GetAction(const std::string& Name)
{
    auto It = Actions.find(Name);
    if (It != Actions.end())
    {
        return &It->second;
    }
    return nullptr;
}