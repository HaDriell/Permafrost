#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/UserInput.h"

struct WindowProperties
{
    std::string Title           = "Window";
    i32         GLVersionMajor  = 4;
    i32         GLVersionMinor  = 5;
    bool        GLCoreProfile   = false;
    bool        GLDebug         = true;
    i32         Width           = 1280;
    i32         Height          = 720;
    bool        Decorated       = true;
    bool        Resizeable      = true;
    bool        Fullscreen      = false;
    bool        VSync           = true;
};

class GLFWwindow;

class Window
{
    friend class WindowEventLoop;
public:
    static std::shared_ptr<Window> Open(const WindowProperties& Properties = WindowProperties());

    void Close();

private:
    void RenderImpl();
    void OpenImpl();
    void CloseImpl();

public:
    WindowProperties        Properties;
    Delegate<>              OnRender;
    UserInput               Input;
private:
    GLFWwindow*             Handle{ nullptr };
};