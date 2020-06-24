#pragma once

#include <memory>
#include <vector>

#include "Permafrost/Graphics/Buffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void ComputeLayout();
    
    void Attach(const std::shared_ptr<VertexBuffer>& VertexBuffer);
    void Detach(const std::shared_ptr<VertexBuffer>& VertexBuffer);

private:
    unsigned int                                Handle;
    std::vector<std::shared_ptr<VertexBuffer>>  AttachedBuffers;
};