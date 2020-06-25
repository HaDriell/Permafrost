#pragma once

#include "Permafrost/Core/CommonTypes.h"

const u32 FNV_Prime = 0x01000193;
const u32 FNV_Seed  = 0x811C9DC5;

inline constexpr u32 Hash_FNV1a(u8 Byte, u32 Hash = FNV_Seed)
{
    return (Byte ^ Hash) * FNV_Prime;
}

u32 Hash_FNV1a(const void* Data, u32 Size, u32 Hash = FNV_Seed);