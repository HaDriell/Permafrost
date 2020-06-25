#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Graphics/Buffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void ComputeLayout();
    
    void Attach(VertexBuffer* VertexBuffer);
    void Detach(VertexBuffer* VertexBuffer);

private:
    u32                         Handle;
    std::vector<VertexBuffer*>  AttachedBuffers;
};