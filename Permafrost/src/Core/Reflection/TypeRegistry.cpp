#include "Permafrost/Core/Reflection/TypeRegistry.h"

#include "Permafrost/Core/Log.h"

std::unordered_map<u32        , TypeDefinition*> TypeRegistry::TypeMap_ID;
std::unordered_map<std::string, TypeDefinition*> TypeRegistry::TypeMap_Name;

void TypeRegistry::Register(TypeDefinition* Type)
{
    assert(Type);
    //Fail when registering multiple times
    assert(TypeRegistry::Resolve(Type->UniqueID) == nullptr);
    assert(TypeRegistry::Resolve(Type->Name) == nullptr);

    TypeRegistry::TypeMap_ID.insert(std::make_pair(Type->UniqueID, Type));
    TypeRegistry::TypeMap_Name.insert(std::make_pair(Type->Name, Type));
}

TypeDefinition* TypeRegistry::Resolve(u32 UniqueID)
{
    auto It = TypeMap_ID.find(UniqueID);
    if (It != TypeMap_ID.end())
    {
        return It->second;
    }
    return nullptr;
}

TypeDefinition* TypeRegistry::Resolve(const std::string& Name)
{
    auto It = TypeMap_Name.find(Name);
    if (It != TypeMap_Name.end())
    {
        return It->second;
    }
    return nullptr;
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




template<> TypeDefinition* TypeRegistry::Resolve<u8>()  { return &TypeDefinition_u8; }
template<> TypeDefinition* TypeRegistry::Resolve<u16>() { return &TypeDefinition_u16; }
template<> TypeDefinition* TypeRegistry::Resolve<u32>() { return &TypeDefinition_u32; }
template<> TypeDefinition* TypeRegistry::Resolve<u64>() { return &TypeDefinition_u64; }

template<> TypeDefinition* TypeRegistry::Resolve<i8>()  { return &TypeDefinition_i8; }
template<> TypeDefinition* TypeRegistry::Resolve<i16>() { return &TypeDefinition_i16; }
template<> TypeDefinition* TypeRegistry::Resolve<i32>() { return &TypeDefinition_i32; }
template<> TypeDefinition* TypeRegistry::Resolve<i64>() { return &TypeDefinition_i64; }

template<> TypeDefinition* TypeRegistry::Resolve<f32>() { return &TypeDefinition_f32; }
template<> TypeDefinition* TypeRegistry::Resolve<f64>() { return &TypeDefinition_f64; }
