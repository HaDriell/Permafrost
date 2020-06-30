#include "Permafrost/Graphics/RenderUtil.h"

#include <glad/glad.h>

Scope<Renderer> RenderUtil::Instance;


void RenderUtil::SetClearColor(f32 R, f32 G, f32 B, f32 A)
{
    glClearColor(R, G, B, A);
}

void RenderUtil::Clear(bool ColorBuffer, bool DepthBuffer, bool StencilBuffer)
{
    GLbitfield Mask = 0;
    if (ColorBuffer) Mask |= GL_COLOR_BUFFER_BIT;
    if (DepthBuffer) Mask |= GL_DEPTH_BUFFER_BIT;
    if (StencilBuffer) Mask |= GL_STENCIL_BUFFER_BIT;
    glClear(Mask);
}


Scope<Renderer>& RenderUtil::Get()
{
    if (!Instance)
    {
        Instance.reset(new Renderer());
    }
    return Instance;
}