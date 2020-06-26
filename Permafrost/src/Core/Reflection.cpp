#include "Permafrost/Core/Reflection.h"

#include "Permafrost/Core/Log.h"

TypeDefinition::TypeDefinition(const std::string& Name, u32 Size, u32 UniqueID, TypeDefinition* Parent)
    : Name(Name)
    , Size(Size)
    , UniqueID(UniqueID)
    , Parent(Parent)
{
    Registry::Register(this);
}

void Registry::Register(TypeDefinition* TypeDefinition)
{
    assert(TypeDefinition);

    {   //Check for UniqueID Collisions
        auto It = UniqueIDTypeMap.find(TypeDefinition->UniqueID);
        if (It != UniqueIDTypeMap.end())
        {
            LOG_CRITICAL("Type ID Collision between {0} and {1}", It->second->Name, TypeDefinition->Name);
            std::exit(1);
        }
    }

    {   //Check for Name Collisions
        auto It = NameTypeMap.find(TypeDefinition->Name);
        if (It != NameTypeMap.end())
        {
            LOG_CRITICAL("Type Name Collision between {0} and {1}", It->second->Name, TypeDefinition->Name);
            std::exit(1);
        }
    }
}

TypeDefinition TypeDefinition_u8 ("u8" , sizeof(u8) , Hash_FNV1a("u8" , 2));
TypeDefinition TypeDefinition_u16("u16", sizeof(u16), Hash_FNV1a("u16", 3));
TypeDefinition TypeDefinition_u32("u32", sizeof(u32), Hash_FNV1a("u32", 3));
TypeDefinition TypeDefinition_u64("u64", sizeof(u64), Hash_FNV1a("u64", 3));
TypeDefinition TypeDefinition_i8 ("i8" , sizeof(i8) , Hash_FNV1a("i8" , 2));
TypeDefinition TypeDefinition_i16("i16", sizeof(i16), Hash_FNV1a("i16", 3));
TypeDefinition TypeDefinition_i32("i32", sizeof(i32), Hash_FNV1a("i32", 3));
TypeDefinition TypeDefinition_i64("i64", sizeof(i64), Hash_FNV1a("i64", 3));
TypeDefinition TypeDefinition_f32("f32", sizeof(f32), Hash_FNV1a("f32", 3));
TypeDefinition TypeDefinition_f64("f64", sizeof(f64), Hash_FNV1a("f64", 3));

template<u8>  TypeDefinition* Registry::Resolve<u8>()  { return &TypeDefinition_u8; }
template<u16> TypeDefinition* Registry::Resolve<u16>() { return &TypeDefinition_u16; }
template<u32> TypeDefinition* Registry::Resolve<u32>() { return &TypeDefinition_u32; }
template<u64> TypeDefinition* Registry::Resolve<u64>() { return &TypeDefinition_u64; }
template<i8>  TypeDefinition* Registry::Resolve<i8>()  { return &TypeDefinition_i8; }
template<i16> TypeDefinition* Registry::Resolve<i16>() { return &TypeDefinition_i16; }
template<i32> TypeDefinition* Registry::Resolve<i32>() { return &TypeDefinition_i32; }
template<i64> TypeDefinition* Registry::Resolve<i64>() { return &TypeDefinition_i64; }
template<f32> TypeDefinition* Registry::Resolve<f32>() { return &TypeDefinition_f32; }
template<f64> TypeDefinition* Registry::Resolve<f64>() { return &TypeDefinition_f64; }