#pragma once

enum class TextureWrap
{
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder,
};

enum class TextureFilter
{
    Nearest,
    NearestMipmapLinear,
    NearestMipmapNearest,
    Linear,
    LinearMipmapLinear,
    LinearMipmapNearest,
};

enum class TextureInternalFormat
{
    R8,
    RG8,
    R8I,
    RG16,
    R32F,
    R32I,
    R16F,
    R16I,
    R8UI,
    RGB8,
    RG8I,
    RG16F,
    RGBA8,
    RG8UI,
    R32UI,
    R16UI,
    RGB16,
    RGB8I,
    SRGB8,
    RG32F,
    RG32I,
    RGBA16,
    RG32UI,
    RGB16I,
    RGB8UI,
    RGB32F,
    RGB32I,
    RGB16F,
    RGB32UI,
    RGB16UI,
    RGB9_E5,
    RGBA16F,
    RGBA16I,
    RGBA8UI,
    RGBA32F,
    RGBA32I,
    RGBA16UI,
    RGB10_A2,
    RGBA32UI,
    R8_SNORM,
    RG8_SNORM,
    R16_SNORM,
    RGB10_A2UI,
    RG16_SNORM,
    RGB8_SNORM,
    RGB16_SNORM,
    RGBA8_SNORM,
    SRGB8_ALPHA8,
    RGBA16_SNORM,
    R11F_G11F_B10F,
    DEPTH24_STENCIL8,
    DEPTH_COMPONENT24,
    DEPTH_COMPONENT16,
    DEPTH32F_STENCIL8,
    DEPTH_COMPONENT32F,
    COMPRESSED_RG_RGTC2,
    COMPRESSED_RED_RGTC1,
    COMPRESSED_SIGNED_RG_RGTC2,
    COMPRESSED_SIGNED_RED_RGTC1,
};

enum class TextureFormat
{
    R, 
    RG, 
    RGB, 
    BGR, 
    RGBA, 
    BGRA, 
    RG_INTEGER,
    RED_INTEGER, 
    RGB_INTEGER,
    BGR_INTEGER,
    RGBA_INTEGER,
    BGRA_INTEGER,
    DEPTH_STENCIL,
    STENCIL_INDEX,
    DEPTH_COMPONENT,
};

enum class TextureDataType
{
    INT, 
    BYTE, 
    FLOAT, 
    SHORT, 
    UNSIGNED_INT, 
    UNSIGNED_BYTE, 
    UNSIGNED_SHORT, 
    UNSIGNED_BYTE_3_3_2, 
    UNSIGNED_SHORT_5_6_5, 
    UNSIGNED_INT_8_8_8_8, 
    UNSIGNED_SHORT_4_4_4_4, 
    UNSIGNED_SHORT_5_5_5_1, 
    UNSIGNED_INT_10_10_10_2,
    UNSIGNED_BYTE_2_3_3_REV, 
    UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_SHORT_5_6_5_REV, 
    UNSIGNED_SHORT_4_4_4_4_REV, 
    UNSIGNED_SHORT_1_5_5_5_REV, 
    UNSIGNED_INT_2_10_10_10_REV
};

unsigned int GLTextureFilter(TextureFilter TextureFilter);
unsigned int GLTextureWrap(TextureWrap Wrap);
unsigned int GLTextureInternalFormat(TextureInternalFormat Format);
unsigned int GLTextureFormat(TextureFormat Format);
unsigned int GLTextureDataType(TextureDataType DataType);

struct Texture2DProperties
{
    TextureWrap WrapX       = TextureWrap::ClampToEdge;
    TextureWrap WrapY       = TextureWrap::ClampToEdge;
    TextureFilter MinFilter = TextureFilter::Linear;
    TextureFilter MagFilter = TextureFilter::Linear;
};

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();

public:
    void Update(TextureInternalFormat InternalFormat, TextureFormat Format, TextureDataType DataType, const unsigned char* Data, unsigned int Width, unsigned int Height);
    void Bind(unsigned int Slot) const;

private:
    unsigned int Handle;
    unsigned int Width;
    unsigned int Height;
};