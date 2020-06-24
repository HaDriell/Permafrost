#pragma once

enum DepthTestMode
{
    Always,     Never,
    Equal,      NotEqual,
    Less,       LessOrEqual,
    Greater,    GreaterOrEqual,
};

enum BlendingFactor
{
    Zero, One, 
    SrcColor, OneMinusSrcColor,
    DstColor, OneMinusDstColor,
    SrcAlpha, OneMinusSrcAlpha,
    DstAlpha, OneMinusDstAlpha,
};

enum BlendingMode
{
    Min, Max, Add, Subtract, ReverseSubtract
};

struct RenderOptions
{
    //Depth Testing Options
    bool            WriteDepth      = true;
    bool            TestDepth       = false;
    DepthTestMode   DepthTestMode   = DepthTestMode::Less;
    //Face Culling Options
    bool            FaceCulling     = false;
    //Blending Options
    bool            Blending            = false;
    BlendingFactor  SrcBlendingFactor   = BlendingFactor::One;
    BlendingFactor  DstBlendingFactor   = BlendingFactor::Zero;
    BlendingMode    BlendingMode        = BlendingMode::Add;


    void Apply() const;
};