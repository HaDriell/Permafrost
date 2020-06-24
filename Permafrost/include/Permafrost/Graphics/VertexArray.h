#pragma once

#include <vector>

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
    unsigned int                Handle;
    std::vector<VertexBuffer*>  AttachedBuffers;
};