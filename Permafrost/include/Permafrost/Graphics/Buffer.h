#pragma once

#include "Permafrost/Core/CommonTypes.h"

enum class VertexAttributeType
{
    Invalid = 0,
    Float, Float2, Float3, Float4,
    Matrix3, Matrix4,
    Int, Int2, Int3, Int4,
    Bool
};

struct VertexAttribute
{
    VertexAttribute(VertexAttributeType Type, const std::string& Name, bool Normalized = false);

    VertexAttributeType Type;
    std::string         Name;
    bool                Normalized;
};

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;

    void SetLayout(const std::vector<VertexAttribute>& Layout) { this->Layout = Layout; }
    inline const std::vector<VertexAttribute>& GetLayout() const { return Layout; }
    inline u32 GetSize() const { return Size; }

    template<typename T>
    void Update(const std::vector<T>& DataBuffer)
    {
        const void* Data = DataBuffer.data();
        u32 Size = DataBuffer.size() * sizeof(T);
        UpdateData(Data, Size);
    }

private:
    void UpdateData(const void* Data, u32 Size);

private:
    u32                             Handle;
    u32                             Size;
    std::vector<VertexAttribute>    Layout;
};

u32 GetGLType(VertexAttributeType Type);
u32 GetSizeOf(VertexAttributeType Type);
u32 GetComponentCount(VertexAttributeType Type);