#include "Permafrost/Core/Hash.h"


u32 Hash_FNV1a(const void* Data, u32 Size, u32 Hash)
{
    const u8* Begin = static_cast<const u8*>(Data);
    const u8* End = Begin + Size;

    for (const u8* Ptr = Begin; Ptr != End; Ptr++)
    {
        Hash = Hash_FNV1a(*Ptr, Hash);
    }
    return Hash;
}