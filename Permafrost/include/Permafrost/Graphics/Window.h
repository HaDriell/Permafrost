#pragma once

#include <memory>
#include <string>

#include "Permafrost/Core/UserInput.h"

struct WindowProperties
{
    std::string Title           = "Window";
    int         GLVersionMajor  = 4;
    int         GLVersionMinor  = 5;
    bool        GLCoreProfile   = false;
    bool        GLDebug         = true;
    int         Width           = 1280;
    int         Height          = 720;
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