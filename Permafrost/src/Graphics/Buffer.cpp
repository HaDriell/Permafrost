#include "Permafrost/Graphics/Buffer.h"

#include <glad/glad.h>

VertexAttribute::VertexAttribute(VertexAttributeType Type, const std::string& Name, bool Normalized)
    : Type(Type)
    , Name(Name)
    , Normalized(Normalized)
{}


VertexBuffer::VertexBuffer()
    : Handle(0)
    , Size(0)
    , Layout()
{
    glGenBuffers(1, &Handle);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &Handle);
}


void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, Handle);
}

void VertexBuffer::UpdateData(const void* Data, u32 Size)
{
    glBindBuffer(GL_ARRAY_BUFFER, Handle);
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STREAM_DRAW);
}

u32 GetGLType(VertexAttributeType Type)
{   
    switch (Type)
    {
        case VertexAttributeType::Float:    return GL_FLOAT;
        case VertexAttributeType::Float2:   return GL_FLOAT;
        case VertexAttributeType::Float3:   return GL_FLOAT;
        case VertexAttributeType::Float4:   return GL_FLOAT;
        case VertexAttributeType::Matrix3:  return GL_FLOAT;
        case VertexAttributeType::Matrix4:  return GL_FLOAT;
        case VertexAttributeType::Int:      return GL_INT;
        case VertexAttributeType::Int2:     return GL_INT;
        case VertexAttributeType::Int3:     return GL_INT;
        case VertexAttributeType::Int4:     return GL_INT;
        case VertexAttributeType::Bool:     return GL_BOOL;
    }
    return 0;
}


u32 GetSizeOf(VertexAttributeType Type)
{
    switch (Type)
    {
        case VertexAttributeType::Float:    return 4;
        case VertexAttributeType::Float2:   return 4 * 2;
        case VertexAttributeType::Float3:   return 4 * 3;
        case VertexAttributeType::Float4:   return 4 * 4;

        case VertexAttributeType::Matrix3:  return 4 * 3 * 3;
        case VertexAttributeType::Matrix4:  return 4 * 4 * 4;

        case VertexAttributeType::Int:      return 4;
        case VertexAttributeType::Int2:     return 4 * 2;
        case VertexAttributeType::Int3:     return 4 * 3;
        case VertexAttributeType::Int4:     return 4 * 4;

        case VertexAttributeType::Bool:     return 1;
    }
    return 0;
}

u32 GetComponentCount(VertexAttributeType Type)
{
    switch (Type)
    {
        case VertexAttributeType::Float:    return 1;
        case VertexAttributeType::Float2:   return 2;
        case VertexAttributeType::Float3:   return 3;
        case VertexAttributeType::Float4:   return 4;

        case VertexAttributeType::Matrix3:  return 3 * 3;
        case VertexAttributeType::Matrix4:  return 4 * 4;

        case VertexAttributeType::Int:      return 1;
        case VertexAttributeType::Int2:     return 2;
        case VertexAttributeType::Int3:     return 3;
        case VertexAttributeType::Int4:     return 4;

        case VertexAttributeType::Bool:     return 1;
    }
    return 0;
}