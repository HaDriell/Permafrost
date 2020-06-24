#pragma once

#include <string>
#include <vector>

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

    template<typename T>
    void Update(const std::vector<T>& DataBuffer)
    {
        const void*     Data = DataBuffer.data();
        unsigned int    Size = DataBuffer.size() * sizeof(T);
        UpdateData(Data, Size);
    }

    void SetLayout(const std::vector<VertexAttribute>& Layout) { this->Layout = Layout; }
    inline const std::vector<VertexAttribute>& GetLayout() const { return Layout; }
    inline unsigned int GetSize() const { return Size; }

private:
    void UpdateData(const void* Data, unsigned int Size);

private:
    unsigned int                    Handle;
    unsigned int                    Size;
    std::vector<VertexAttribute>    Layout;
};

unsigned int GetGLType(VertexAttributeType Type);
unsigned int GetSizeOf(VertexAttributeType Type);
unsigned int GetComponentCount(VertexAttributeType Type);