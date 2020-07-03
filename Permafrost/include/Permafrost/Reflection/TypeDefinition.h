#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Hash.h"

struct TypeDefinition
{
    const std::string       Name;
    const u32               Size;
    const u32               UniqueID;
    const TypeDefinition*   Parent;
    
    TypeDefinition(const std::string& Name, u32 Size, u32 UniqueID, TypeDefinition* Parent = nullptr);

private:
    TypeDefinition() = delete;
    TypeDefinition(const TypeDefinition&) = delete;
    TypeDefinition& operator=(const TypeDefinition&) = delete;
};

