#pragma once


class Renderer;

class IDrawable
{
public:
    virtual void Draw(Renderer* Renderer) = 0;
};