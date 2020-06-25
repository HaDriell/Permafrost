#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Hash.h"

#define ENABLE_REFLECTION(Type, Parent)         \
private:                                        \
    static TypeDefinition StaticTypeDefinition; \
public:                                         \
    static TypeDefinition* StaticClass();       \
//ENABLE_REFLECTION MACRO END

#define IMPLEMENT_REFLECTION(Type, Parent)      \
TypeDefinition Type::StaticTypeDefinition       \
(#Type, sizeof(Type), ); \
//IMPLEMENT_REFLECTION END

struct TypeDefinition
{
    const std::string       Name;
    const u32               Size;
    const u32               UniqueID;
    const TypeDefinition*   Parent;
    
    TypeDefinition(const std::string& Name, u32 Size, u32 UniqueID, TypeDefinition* Parent)
        : Name(Name)
        , Size(Size)
        , UniqueID(UniqueID)
        , Parent(Parent)
    {}
};

class Registry
{
    Registry() = delete;
public:

    template<class T>
    static TypeDefinition* Resolve() { return T::StaticClass(); }

    static TypeDefinition* Resolve(u32 UniqueID);

    static TypeDefinition* Resolve(std::string& Name);

    static void Register(TypeDefinition* Type);
private:
    static std::unordered_map<u32, TypeDefinition*> TypeDefinitions;
};