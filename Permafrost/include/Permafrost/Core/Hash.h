#pragma once
#include <type_traits>

#include "Permafrost/Core/CommonTypes.h"

const u32 FNV_Prime = 0x01000193;
const u32 FNV_Seed  = 0x811C9DC5;

inline constexpr u32 Hash_FNV1a(u8 Byte, u32 Hash = FNV_Seed)
{
    return (Byte ^ Hash) * FNV_Prime;
}

u32 Hash_FNV1a(const void* Data, u32 Size, u32 Hash = FNV_Seed);


template<typename T, class U = typename std::enable_if_t<std::is_pointer<T>::value>>
u32 Hash_FNV1a(const T& Data, u32 Hash = FNV_Seed)
{
    return Hash_FNV1a((const void*) Data, sizeof(T), Hash);
}

