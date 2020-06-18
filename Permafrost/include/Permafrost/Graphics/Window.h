#pragma once

#include <string>

#include "Permafrost/Core/UserInput.h"

struct WindowProperties
{
    std::string Title           = "Window";
    uint8_t     GLVersionMajor  = 4;
    uint8_t     GLVersionMinor  = 5;
    bool        GLCoreProfile   = false;
    uint32_t    Width           = 1280;
    uint32_t    Height          = 720;
    bool        Decorated       = true;
    bool        Resizeable      = true;
    bool        Fullscreen      = false;
    bool        VSync           = true;
};

class GLFWwindow;

class Window
{
    friend class GraphicsModule;
public:
    Window() : Handle(nullptr) {}



public:
    bool IsOpen() const;
    bool ShouldClose() const;
private:



public:
    WindowProperties    Properties;
    Delegate<>          OnRender;
    UserInput           Input;
private:
    GLFWwindow*         Handle { nullptr };
};