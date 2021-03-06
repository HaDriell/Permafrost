#include "Permafrost/Reflection/TypeDefinition.h"

#include "Permafrost/Reflection/TypeRegistry.h"

TypeDefinition::TypeDefinition(const std::string& Name, u32 Size, u32 UniqueID, TypeDefinition* Parent)
    : Name(Name)
    , Size(Size)
    , UniqueID(UniqueID)
    , Parent(Parent)
{
    TypeRegistry::Register(this);
}
