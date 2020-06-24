#include "Permafrost/Graphics/RenderOptions.h"

#include <glad/glad.h>


GLenum GLDepthTestMode(DepthTestMode Mode)
{
    switch (Mode)
    {
        case Always:            return GL_ALWAYS;
        case Never:             return GL_NEVER;
        case Equal:             return GL_EQUAL;
        case NotEqual:          return GL_NOTEQUAL;
        case Less:              return GL_LESS;
        case LessOrEqual:       return GL_LEQUAL;
        case Greater:           return GL_GREATER;
        case GreaterOrEqual:    return GL_GEQUAL;
    }
    return GL_FALSE;
}

GLenum GLBlendFactor(BlendingFactor Factor)
{
    switch (Factor)
    {
        case Zero:              return GL_ZERO;
        case One:               return GL_ONE;
        case SrcColor:          return GL_SRC_ALPHA;
        case DstColor:          return GL_DST_ALPHA;
        case SrcAlpha:          return GL_SRC_COLOR;
        case DstAlpha:          return GL_DST_COLOR;
        case OneMinusSrcAlpha:  return GL_ONE_MINUS_SRC_ALPHA;
        case OneMinusDstAlpha:  return GL_ONE_MINUS_DST_ALPHA;
        case OneMinusSrcColor:  return GL_ONE_MINUS_SRC_COLOR;
        case OneMinusDstColor:  return GL_ONE_MINUS_DST_COLOR;
    }
    return GL_FALSE;
}

GLenum GLBlendMode(BlendingMode Mode)
{
    switch (Mode)
    {
        case Min:               return GL_MIN;
        case Max:               return GL_MAX;
        case Add:               return GL_FUNC_ADD;
        case Subtract:          return GL_FUNC_SUBTRACT;
        case ReverseSubtract:   return GL_FUNC_REVERSE_SUBTRACT;
    }
    return GL_FALSE;
}

void RenderOptions::Apply() const
{
    glDepthMask(WriteDepth ? GL_TRUE : GL_FALSE);
    if (!TestDepth)
    {
        glDisable(GL_DEPTH_TEST);
    }
    else
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GLDepthTestMode(DepthTestMode));
    }

    if (!Blending)
    {
        glDisable(GL_BLEND);
    }
    else
    {
        glEnable(GL_BLEND);
        glBlendEquation(GLBlendMode(BlendingMode));
        glBlendFunc(GLBlendFactor(SrcBlendingFactor), GLBlendFactor(DstBlendingFactor));
    }
    
    if (!FaceCulling)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK); // Force default
    }
}