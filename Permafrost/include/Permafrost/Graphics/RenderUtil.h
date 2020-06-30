#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Graphics/Renderer.h"

class RenderUtil
{
    RenderUtil() = delete;
public:
    
    static void SetClearColor(f32 R, f32 G, f32 B, f32 A = 1);
    static void Clear(bool ColorBuffer = true, bool DepthBuffer = true, bool StencilBuffer = false);

public:
    static Scope<Renderer>& Get();
    
private:
    static Scope<Renderer> Instance;
};