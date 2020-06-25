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


Renderer::Renderer()
{
    RenderThread    = std::this_thread::get_id();
    Drawing         = false;

    //Setup RenderOptions
    BatchRenderOptions.Blending = true;
    BatchRenderOptions.SrcBlendingFactor = BlendingFactor::SrcAlpha;
    BatchRenderOptions.DstBlendingFactor = BlendingFactor::OneMinusSrcAlpha;
    BatchRenderOptions.BlendingMode = BlendingMode::Add;

    BatchRenderOptions.FaceCulling = false;

    //Setup Shader
    ShaderSources Sources;
    Sources[ShaderType::Vertex]     = Renderer_VertexShaderSource;
    Sources[ShaderType::Fragment]   = Renderer_FragmentShaderSource;
    BatchShader.Compile(Sources);
    BatchShader.Debug();

    //Setup Vertex Buffer
    std::vector<VertexAttribute> Vertex2DLayout;
    Vertex2DLayout.push_back(VertexAttribute(VertexAttributeType::Float4, "Position"));
    Vertex2DLayout.push_back(VertexAttribute(VertexAttributeType::Float4, "Color"));
    Vertex2DLayout.push_back(VertexAttribute(VertexAttributeType::Float2, "UV"));
    Vertex2DLayout.push_back(VertexAttribute(VertexAttributeType::Float, "TextureID"));
    BatchVertexBuffer.SetLayout(Vertex2DLayout);

    //Setup Vertex Array
    BatchVertexArray.Attach(&BatchVertexBuffer);
    BatchVertexArray.ComputeLayout();
}

Renderer::~Renderer()
{
    AssertRenderThread();
    AssertNotDrawing();
}


void Renderer::Begin(u32 BatchQuadCapacity)
{
    AssertRenderThread();
    AssertNotDrawing();
    Drawing = true;

    //Prepare Vertex Batch
    Vertices.clear();
    Vertices.reserve(BatchQuadCapacity * 6);

    //Prepare Transformation Stack
    TransformationStack.clear();
    TransformationStack.push_back(glm::mat4(1.0f));
}

void Renderer::Flush()
{
    AssertRenderThread();
    AssertDrawing();

    if (!Vertices.empty())
    {
        u32 VertexCount = Vertices.size(); 
        //Upload & Reset Vertices
        BatchVertexBuffer.Bind();
        BatchVertexBuffer.Update(Vertices);
        Vertices.clear();

        //Execute Draw Call
        BatchRenderOptions.Apply();
        BatchVertexArray.Bind();
        BatchShader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, VertexCount);
    }
}

void Renderer::End()
{
    AssertRenderThread();
    AssertDrawing();
    Flush();
    Drawing = false;
}

void Renderer::Push(const glm::mat4& Transform, bool Absolute)
{
    AssertRenderThread();
    AssertDrawing();

    if (Absolute)
    {
        TransformationStack.push_back(TransformationStack.back() * Transform);
    }
    else
    {
        TransformationStack.push_back(TransformationStack.front() * Transform);
    }
}

void Renderer::Pop()
{
    AssertRenderThread();
    AssertDrawing();

    if (TransformationStack.size() > 1)
    {
        TransformationStack.pop_back();
    }
}


void Renderer::Draw(IDrawable* Drawable)
{
    AssertRenderThread();
    AssertDrawing();
    Drawable->Draw(this);
}

void Renderer::DrawRect(f32 X, f32 Y, f32 With, f32 Height, const glm::vec4& Color)
{
    AssertRenderThread();
    AssertDrawing();
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
    Vertices.push_back(Vertex0);
    Vertices.push_back(Vertex2);
    Vertices.push_back(Vertex3);
}