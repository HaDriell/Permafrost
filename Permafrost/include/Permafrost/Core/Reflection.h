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
};

class Registry
{
    Registry() = delete;
public:

    template<class T>
    static TypeDefinition* Resolve()
    {
        return T::StaticClass();
    }

    //Primitive Specializations
    template<u8>  static TypeDefinition* Resolve<u8>();
    template<u16> static TypeDefinition* Resolve<u16>();
    template<u32> static TypeDefinition* Resolve<u32>();
    template<u64> static TypeDefinition* Resolve<u64>();
    template<i8>  static TypeDefinition* Resolve<i8>();
    template<i16> static TypeDefinition* Resolve<i16>();
    template<i32> static TypeDefinition* Resolve<i32>();
    template<i64> static TypeDefinition* Resolve<i64>();
    template<f32> static TypeDefinition* Resolve<f32>();
    template<f64> static TypeDefinition* Resolve<f64>();

    static TypeDefinition* Resolve(u32 UniqueID);

    static TypeDefinition* Resolve(std::string& Name);

    static void Register(TypeDefinition* Type);
private:
    static std::unordered_map<u32, TypeDefinition*>         UniqueIDTypeMap;
    static std::unordered_map<std::string, TypeDefinition*> NameTypeMap;
};



#define ENABLE_REFLECTION(Type)                 \
private:                                        \
    static TypeDefinition StaticClassDefinition;\
public:                                         \
    static TypeDefinition* StaticClass();       \
//ENABLE_REFLECTION MACRO END

#define IMPLEMENT_REFLECTION(Type)              \
TypeDefinition Type::StaticClassDefinition(     \
    #Type,                                      \
    sizeof(Type),                               \
    Hash_FNV1a(#Type, sizeof(#Type)));          \
//IMPLEMENT_REFLECTION END

#define IMPLEMENT_CHILD_REFLECTION(Type, Parent)\
TypeDefinition Type::StaticClassDefinition(     \
    #Type,                                      \
    sizeof(Type),                               \
    Hash_FNV1a(#Type, sizeof(#Type)),           \
    Parent::StaticClass());                     \
//IMPLEMENT_CHILD_REFLECTION END
