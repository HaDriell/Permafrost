#include "Permafrost/Graphics/Renderer.h"

#include <glad/glad.h>

#include "Permafrost/Core/Log.h"

static const std::string Renderer_VertexShaderSource = R"(
    #version 400 core

    in vec4     Position;
    in vec4     Color;
    in vec2     UV;
    in float    TextureID;

    out vec4    vs_Position;
    out vec4    vs_Color;
    out vec2    vs_UV;
    out float   vs_TextureID;

    void main()
    {
        gl_Position     = Position;

        vs_Position     = Position;
        vs_Color        = Color;
        vs_UV           = UV;
        vs_TextureID    = TextureID;
    }
)";

static const std::string Renderer_FragmentShaderSource = R"(
    #version 400 core

    in vec4     vs_Position;
    in vec4     vs_Color;
    in vec2     vs_UV;
    in float    vs_TextureID;

    out vec4    fs_Color;

    uniform sampler2D u_Texture[32];

    void main()
    {
        fs_Color = vs_Color;
    }
)";


void Renderer::Begin(unsigned int BatchQuadCapacity)
{
    AssertNotDrawing();
    Drawing = true;
    CurrentThread = std::this_thread::get_id();

    //Lazy Shader Initialization
    if (!BatchShader)
    {
        LOG_INFO("Initializing BatchShader");
        BatchShader.reset(new Shader());

        ShaderSources Sources;
        Sources[ShaderType::Vertex]     = Renderer_VertexShaderSource;
        Sources[ShaderType::Fragment]   = Renderer_FragmentShaderSource;

        BatchShader->Compile(Sources);
        BatchShader->Debug();
    }

    if (!BatchVertexArray)
    {
        BatchVertexArray.reset(new VertexArray());
    }
    
    if (!BatchVertexBuffer)
    {
        BatchVertexBuffer.reset(new VertexBuffer());
        BatchVertexArray->Attach(BatchVertexBuffer);
    }

    //Prepare Vertex Batch
    Vertices.clear();
    Vertices.reserve(BatchQuadCapacity * 6);

    //Prepare Transformation Stack
    TransformationStack.clear();
    TransformationStack.push_back(glm::mat4());
}

void Renderer::Flush()
{
    AssertCurrent();
    AssertDrawing();

    if (!Vertices.empty())
    {
        //Upload & Reset Vertices
        BatchVertexBuffer->Bind();
        BatchVertexBuffer->Update(Vertices);

        //Execute Draw Call
        BatchVertexArray->Bind();
        BatchShader->Bind();
        glDrawArrays(GL_TRIANGLES, 0, Vertices.size());

        //Reset Batch
        Vertices.clear();
    }
}

void Renderer::End()
{
    AssertCurrent();
    AssertDrawing();
    Flush();
    Drawing = false;
}

void Renderer::Push(const glm::mat4& Transform, bool Absolute)
{
    AssertCurrent();
    AssertDrawing();

    if (Absolute)
    {
        TransformationStack.push_back(Transform);
    }
    else
    {
        TransformationStack.push_back(GetTransform() * Transform);
    }
}

void Renderer::Pop()
{
    AssertCurrent();
    AssertDrawing();

    if (TransformationStack.size() > 1)
    {
        TransformationStack.pop_back();
    }
}


void Renderer::Draw(IDrawable* Drawable)
{
    Drawable->Draw(this);
}

void Renderer::DrawRect(float X, float Y, float With, float Height, const glm::vec4& Color)
{
    if (Vertices.size() + 6 >= Vertices.capacity())
    {
        Flush();
    }

    Vertex2D Vertex0;
    Vertex0.Position    = GetTransform() * glm::vec4(X, Y, 0.0f, 1.0f);
    Vertex0.Color       = Color;
    Vertex0.UV          = glm::vec2(0);
    Vertex0.TextureID   = -1;

    Vertex2D Vertex1;
    Vertex1.Position    = GetTransform() * glm::vec4(X + With, Y, 0.0f, 1.0f);
    Vertex1.Color       = Color;
    Vertex1.UV          = glm::vec2(0);
    Vertex1.TextureID   = -1;

    Vertex2D Vertex2;
    Vertex2.Position    = GetTransform() * glm::vec4(X + With, Y + Height, 0.0f, 1.0f);
    Vertex2.Color       = Color;
    Vertex2.UV          = glm::vec2(0);
    Vertex2.TextureID   = -1;

    Vertex2D Vertex3;
    Vertex3.Position    = GetTransform() * glm::vec4(X, Y + Height, 0.0f, 1.0f);
    Vertex3.Color       = Color;
    Vertex3.UV          = glm::vec2(0);
    Vertex3.TextureID   = -1;

    //Push Triangles 1
    Vertices.push_back(Vertex0);
    Vertices.push_back(Vertex1);
    Vertices.push_back(Vertex2);
    //Push Triangle 2
    Vertices.push_back(Vertex2);
    Vertices.push_back(Vertex3);
    Vertices.push_back(Vertex0);
}