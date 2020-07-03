#pragma once

#include "Permafrost/Core/CommonTypes.h"

class ByteBuffer
{
    void Read(u8& Value);
    void Read(u16& Value);
    void Read(u32& Value);
    void Read(u64& Value);
    void Read(i8& Value);
    void Read(i16& Value);
    void Read(i32& Value);
    void Read(i64& Value);
    void Read(f32& Value);
    void Read(f64& Value);
private:
    std::vector<u8> Buffer;
    u32             Position;
};