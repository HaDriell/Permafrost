#include "Permafrost/Graphics/Texture2D.h"

#include <glad/glad.h>

unsigned int GLTextureFilter(TextureFilter Filter)
{
    switch (Filter)
    {
        case TextureFilter::Nearest:                return GL_NEAREST;
        case TextureFilter::NearestMipmapLinear:    return GL_NEAREST_MIPMAP_LINEAR;
        case TextureFilter::NearestMipmapNearest:   return GL_NEAREST_MIPMAP_NEAREST;
        case TextureFilter::Linear:                 return GL_LINEAR;
        case TextureFilter::LinearMipmapLinear:     return GL_LINEAR_MIPMAP_LINEAR;
        case TextureFilter::LinearMipmapNearest:    return GL_LINEAR_MIPMAP_NEAREST;
    }
    return GL_FALSE;
}

unsigned int GLTextureWrap(TextureWrap Wrap)
{
    switch (Wrap)
    {
        case TextureWrap::ClampToBorder:    return GL_CLAMP_TO_BORDER;
        case TextureWrap::ClampToEdge:      return GL_CLAMP_TO_EDGE;
        case TextureWrap::Repeat:           return GL_REPEAT;
        case TextureWrap::MirroredRepeat:   return GL_MIRRORED_REPEAT;
    }
    return GL_FALSE;
}

unsigned int GLTextureInternalFormat(TextureInternalFormat Format)
{
    switch (Format)
    {
    case TextureInternalFormat::R8:                             return GL_R8;
    case TextureInternalFormat::RG8:                            return GL_RG8;
    case TextureInternalFormat::R8I:                            return GL_R8I;
    case TextureInternalFormat::RG16:                           return GL_RG16;
    case TextureInternalFormat::R32F:                           return GL_R32F;
    case TextureInternalFormat::R32I:                           return GL_R32I;
    case TextureInternalFormat::R16F:                           return GL_R16F;
    case TextureInternalFormat::R16I:                           return GL_R16I;
    case TextureInternalFormat::R8UI:                           return GL_R8UI;
    case TextureInternalFormat::RGB8:                           return GL_RGB8;
    case TextureInternalFormat::RG8I:                           return GL_RG8I;
    case TextureInternalFormat::RG16F:                          return GL_RG16F;
    case TextureInternalFormat::RGBA8:                          return GL_RGBA8;
    case TextureInternalFormat::RG8UI:                          return GL_RG8UI;
    case TextureInternalFormat::R32UI:                          return GL_R32UI;
    case TextureInternalFormat::R16UI:                          return GL_R16UI;
    case TextureInternalFormat::RGB16:                          return GL_RGB16;
    case TextureInternalFormat::RGB8I:                          return GL_RGB8I;
    case TextureInternalFormat::SRGB8:                          return GL_SRGB8;
    case TextureInternalFormat::RG32F:                          return GL_RG32F;
    case TextureInternalFormat::RG32I:                          return GL_RG32I;
    case TextureInternalFormat::RGBA16:                         return GL_RGBA16;
    case TextureInternalFormat::RG32UI:                         return GL_RG32UI;
    case TextureInternalFormat::RGB16I:                         return GL_RGB16I;
    case TextureInternalFormat::RGB8UI:                         return GL_RGB8UI;
    case TextureInternalFormat::RGB32F:                         return GL_RGB32F;
    case TextureInternalFormat::RGB32I:                         return GL_RGB32I;
    case TextureInternalFormat::RGB16F:                         return GL_RGB16F;
    case TextureInternalFormat::RGB16UI:                        return GL_RGB16UI;
    case TextureInternalFormat::RGB32UI:                        return GL_RGB32UI;
    case TextureInternalFormat::RGB9_E5:                        return GL_RGB9_E5;
    case TextureInternalFormat::RGBA16F:                        return GL_RGBA16F;
    case TextureInternalFormat::RGBA16I:                        return GL_RGBA16I;
    case TextureInternalFormat::RGBA8UI:                        return GL_RGBA8UI;
    case TextureInternalFormat::RGBA32F:                        return GL_RGBA32F;
    case TextureInternalFormat::RGBA32I:                        return GL_RGBA32I;
    case TextureInternalFormat::RGBA16UI:                       return GL_RGBA16UI;
    case TextureInternalFormat::RGB10_A2:                       return GL_RGB10_A2;
    case TextureInternalFormat::RGBA32UI:                       return GL_RGBA32UI;
    case TextureInternalFormat::R8_SNORM:                       return GL_R8_SNORM;
    case TextureInternalFormat::RG8_SNORM:                      return GL_RG8_SNORM;
    case TextureInternalFormat::R16_SNORM:                      return GL_R16_SNORM;
    case TextureInternalFormat::RGB10_A2UI:                     return GL_RGB10_A2UI;
    case TextureInternalFormat::RG16_SNORM:                     return GL_RG16_SNORM;
    case TextureInternalFormat::RGB8_SNORM:                     return GL_RGB8_SNORM;
    case TextureInternalFormat::RGB16_SNORM:                    return GL_RGB16_SNORM;
    case TextureInternalFormat::RGBA8_SNORM:                    return GL_RGBA8_SNORM;
    case TextureInternalFormat::SRGB8_ALPHA8:                   return GL_SRGB8_ALPHA8;
    case TextureInternalFormat::RGBA16_SNORM:                   return GL_RGBA16_SNORM;
    case TextureInternalFormat::R11F_G11F_B10F:                 return GL_R11F_G11F_B10F;
    case TextureInternalFormat::DEPTH24_STENCIL8:               return GL_DEPTH24_STENCIL8;
    case TextureInternalFormat::DEPTH_COMPONENT24:              return GL_DEPTH_COMPONENT24;
    case TextureInternalFormat::DEPTH_COMPONENT16:              return GL_DEPTH_COMPONENT16;
    case TextureInternalFormat::DEPTH32F_STENCIL8:              return GL_DEPTH32F_STENCIL8;
    case TextureInternalFormat::DEPTH_COMPONENT32F:             return GL_DEPTH_COMPONENT32F;
    case TextureInternalFormat::COMPRESSED_RG_RGTC2:            return GL_COMPRESSED_RG_RGTC2;
    case TextureInternalFormat::COMPRESSED_RED_RGTC1:           return GL_COMPRESSED_RED_RGTC1;
    case TextureInternalFormat::COMPRESSED_SIGNED_RG_RGTC2:     return GL_COMPRESSED_SIGNED_RG_RGTC2;
    case TextureInternalFormat::COMPRESSED_SIGNED_RED_RGTC1:    return GL_COMPRESSED_SIGNED_RED_RGTC1;
    }
    return GL_FALSE;
}

unsigned int GLTextureFormat(TextureFormat Format)
{
    switch (Format)
    {
        case TextureFormat::R:                 return GL_RED;
        case TextureFormat::RG:                return GL_RG;
        case TextureFormat::RGB:               return GL_RGB;
        case TextureFormat::BGR:               return GL_BGR;
        case TextureFormat::RGBA:              return GL_RGBA;
        case TextureFormat::BGRA:              return GL_BGRA;
        case TextureFormat::RG_INTEGER:        return GL_RG_INTEGER;
        case TextureFormat::RED_INTEGER:       return GL_RED_INTEGER;
        case TextureFormat::RGB_INTEGER:       return GL_RGB_INTEGER;
        case TextureFormat::BGR_INTEGER:       return GL_BGR_INTEGER;
        case TextureFormat::RGBA_INTEGER:      return GL_RGBA_INTEGER;
        case TextureFormat::BGRA_INTEGER:      return GL_BGRA_INTEGER;
        case TextureFormat::DEPTH_STENCIL:     return GL_DEPTH_STENCIL;
        case TextureFormat::STENCIL_INDEX:     return GL_STENCIL_INDEX;
        case TextureFormat::DEPTH_COMPONENT:   return GL_DEPTH_COMPONENT;
    }
    return GL_FALSE;
}

unsigned int GLTextureDataType(TextureDataType Type)
{
    switch (Type)
    {
        case TextureDataType::INT:                          return GL_INT;
        case TextureDataType::BYTE:                         return GL_BYTE;
        case TextureDataType::SHORT:                        return GL_SHORT;
        case TextureDataType::FLOAT:                        return GL_FLOAT;
        case TextureDataType::UNSIGNED_INT:                 return GL_UNSIGNED_INT;
        case TextureDataType::UNSIGNED_BYTE:                return GL_UNSIGNED_BYTE;
        case TextureDataType::UNSIGNED_SHORT:               return GL_UNSIGNED_SHORT;
        case TextureDataType::UNSIGNED_BYTE_3_3_2:          return GL_UNSIGNED_BYTE_3_3_2;
        case TextureDataType::UNSIGNED_INT_8_8_8_8:         return GL_UNSIGNED_INT_8_8_8_8;
        case TextureDataType::UNSIGNED_SHORT_5_6_5:         return GL_UNSIGNED_SHORT_5_6_5;
        case TextureDataType::UNSIGNED_SHORT_5_5_5_1:       return GL_UNSIGNED_SHORT_5_5_5_1;
        case TextureDataType::UNSIGNED_SHORT_4_4_4_4:       return GL_UNSIGNED_SHORT_4_4_4_4;
        case TextureDataType::UNSIGNED_INT_10_10_10_2:      return GL_UNSIGNED_INT_10_10_10_2;
        case TextureDataType::UNSIGNED_BYTE_2_3_3_REV:      return GL_UNSIGNED_BYTE_2_3_3_REV;
        case TextureDataType::UNSIGNED_INT_8_8_8_8_REV:     return GL_UNSIGNED_INT_8_8_8_8_REV;
        case TextureDataType::UNSIGNED_SHORT_5_6_5_REV:     return GL_UNSIGNED_SHORT_5_6_5_REV;
        case TextureDataType::UNSIGNED_SHORT_4_4_4_4_REV:   return GL_UNSIGNED_SHORT_4_4_4_4_REV; 
        case TextureDataType::UNSIGNED_SHORT_1_5_5_5_REV:   return GL_UNSIGNED_SHORT_1_5_5_5_REV; 
        case TextureDataType::UNSIGNED_INT_2_10_10_10_REV:  return GL_UNSIGNED_INT_2_10_10_10_REV;
    }
    return GL_FALSE;
}

Texture2D::Texture2D() 
    : Handle(0)
{
    glGenTextures(1, &Handle);
}


Texture2D::~Texture2D()
{
    glDeleteTextures(1, &Handle);
}

void Texture2D::Update(TextureInternalFormat InternalFormat, TextureFormat Format, TextureDataType DataType, const unsigned char* Data, unsigned int Width, unsigned int Height)
{
    GLenum GLInternalFormat = GLTextureInternalFormat(InternalFormat);
    GLenum GLFormat         = GLTextureFormat(Format);
    GLenum GLDataType       = GLTextureDataType(DataType);
    glBindTexture(GL_TEXTURE_2D, Handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GLInternalFormat, Width, Height, 0, GLFormat, GLDataType, Data);
}

void Texture2D::Bind(unsigned int Slot) const
{
    glActiveTexture(GL_TEXTURE0 + Slot);
    glBindTexture(GL_TEXTURE_2D, Handle);
}