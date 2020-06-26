#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Hash.h"
#include "Permafrost/Core/Reflection/TypeDefinition.h"

class TypeRegistry
{
    TypeRegistry() = delete;

public:

    template<typename T>
    static TypeDefinition* Resolve()
    {
        return T::StaticClass();
    }

    static TypeDefinition* Resolve(u32 UniqueID);
    static TypeDefinition* Resolve(const std::string& Name);

    static void Register(TypeDefinition* Type);
private:
    static std::unordered_map<u32        , TypeDefinition*> TypeMap_ID;
    static std::unordered_map<std::string, TypeDefinition*> TypeMap_Name;
};




template<> TypeDefinition* TypeRegistry::Resolve<u8>();
template<> TypeDefinition* TypeRegistry::Resolve<u16>();
template<> TypeDefinition* TypeRegistry::Resolve<u32>();
template<> TypeDefinition* TypeRegistry::Resolve<u64>();

template<> TypeDefinition* TypeRegistry::Resolve<i8>();
template<> TypeDefinition* TypeRegistry::Resolve<i16>();
template<> TypeDefinition* TypeRegistry::Resolve<i32>();
template<> TypeDefinition* TypeRegistry::Resolve<i64>();

template<> TypeDefinition* TypeRegistry::Resolve<f32>();
template<> TypeDefinition* TypeRegistry::Resolve<f64>();
