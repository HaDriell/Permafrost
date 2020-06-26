#pragma once

#include "Permafrost/Core/Reflection/TypeDefinition.h"
#include "Permafrost/Core/Reflection/TypeRegistry.h"

#define REFLECT(Type)                           \
private:                                        \
    static TypeDefinition s_StaticClass;        \
public:                                         \
    static TypeDefinition* StaticClass()        \
    { return &s_StaticClass; }                  \
//REFLECT MACRO END


#define REFLECT_IMPL(Type)                      \
TypeDefinition Type::s_StaticClass(             \
    #Type,                                      \
    sizeof(Type),                               \
    Hash_FNV1a(#Type, sizeof(#Type))            \
);                                              \
//REFLECT_IMPL END


#define REFLECT_IMPL_CHILD(Type, Parent)        \
TypeDefinition Type::s_StaticClass(             \
    #Type,                                      \
    sizeof(Type),                               \
    Hash_FNV1a(#Type, sizeof(#Type)),           \
    TypeRegistry::Resolve<Parent>()             \
);                                              \
//REFLECT_IMPL END
