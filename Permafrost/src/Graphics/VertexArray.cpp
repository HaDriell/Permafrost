#include "Permafrost/Graphics/VertexArray.h"

#include <algorithm>
#include <glad/glad.h>


VertexArray::VertexArray()
    : Handle(0)
{
    glGenVertexArrays(1, &Handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &Handle);
}

void VertexArray::Bind() const
{
    glBindVertexArray(Handle);
}

void VertexArray::Attach(VertexBuffer* VertexBuffer)
{
    AttachedBuffers.push_back(VertexBuffer);
}

void VertexArray::Detach(VertexBuffer* VertexBuffer)
{
    auto It = std::find(AttachedBuffers.begin(), AttachedBuffers.end(), VertexBuffer);
    if (It != AttachedBuffers.end())
    {
        AttachedBuffers.erase(It);
    }
}

void VertexArray::ComputeLayout()
{
    i32 MaxVertexAttributes = 16; // This is the minimum supported amount for OpenGL compliance
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MaxVertexAttributes);

    glBindVertexArray(Handle);

    i32 VertexAttributeIndex = 0;
    for (auto Buffer : AttachedBuffers)
    {
        Buffer->Bind();

        //Compute Stride for this Buffer Layout
        u32 Stride = 0;
        for (auto VertexAttribute : Buffer->GetLayout())
        {
            Stride += GetSizeOf(VertexAttribute.Type);
        }

        std::uintptr_t Offset = 0;
        for (auto VertexAttribute : Buffer->GetLayout())
        {
            //Check for Vertex Attribute limit
            if (VertexAttributeIndex >= MaxVertexAttributes)
            {
                return;
            }

            //Enable & Setup Vertex Attribute
            glEnableVertexAttribArray(VertexAttributeIndex);
            glVertexAttribPointer(
                VertexAttributeIndex,
                GetComponentCount(VertexAttribute.Type),
                GetGLType(VertexAttribute.Type),
                VertexAttribute.Normalized,
                Stride,
                (const void*) Offset
            );

            Offset += GetSizeOf(VertexAttribute.Type);
            VertexAttributeIndex++;
        }
    }

    //Force disabling unused Attribute Indices
    for (i32 UnusedVertexAttributeIndex = VertexAttributeIndex; UnusedVertexAttributeIndex < MaxVertexAttributes; UnusedVertexAttributeIndex++)
    {
        glDisableVertexAttribArray(UnusedVertexAttributeIndex);
    }
}