#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <thread>

#include "Permafrost/Graphics/Buffer.h"
#include "Permafrost/Graphics/Drawable.h"
#include "Permafrost/Graphics/Shader.h"
#include "Permafrost/Graphics/Texture2D.h"
#include "Permafrost/Graphics/VertexArray.h"
#include "Permafrost/Graphics/RenderOptions.h"

struct Vertex2D
{
    glm::vec4   Position;
    glm::vec4   Color;
    glm::vec2   UV;
    float       TextureID;
};


class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Begin(unsigned int BatchQuadCapacity = 10000);
    void Flush();
    void End();

    void Push(const glm::mat4& Transform, bool Absolute = false);
    void Pop();

    void Draw(IDrawable* Drawable);
    void DrawRect(float X, float Y, float With, float Height, const glm::vec4& Color = glm::vec4(1));

    inline const glm::mat4& GetTransform() const { return TransformationStack.front(); }

private:

    //TODO : Replace with MACROS and enable only on Debug
    inline void AssertRenderThread() const { assert(RenderThread == std::this_thread::get_id()); }
    inline void AssertDrawing() const { assert(Drawing); }
    inline void AssertNotDrawing() const { assert(!Drawing); }

private:
    std::thread::id         RenderThread;

    bool                    Drawing;
    std::vector<glm::mat4>  TransformationStack;
    std::vector<Vertex2D>   Vertices;

    RenderOptions           BatchRenderOptions;
    Shader                  BatchShader;
    VertexArray             BatchVertexArray;
    VertexBuffer            BatchVertexBuffer;
};