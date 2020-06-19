#include "Permafrost/Graphics/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Core/Log.h"
#include "Permafrost/Graphics/WindowEventLoop.h"


Window::Window()
    : Opened(false)
    , Handle(nullptr)
{}


Window::~Window()
{
    CloseImpl();
}

void Window::Open()
{
    Opened = true;
    WindowEventLoop::Get().Register(this);
    WindowEventLoop::Get().WakeUp();
}

void Window::Close()
{
    Opened = false;
    WindowEventLoop::Get().Unregister(this);
    WindowEventLoop::Get().WakeUp();
}


void Window::RenderImpl()
{
    if (Handle == nullptr)
        return;

    glfwMakeContextCurrent(Handle);
    OnRender.Broadcast();
    glfwSwapBuffers(Handle);
}

void Window::OpenImpl()
{
    if (!Opened || Handle != nullptr)
        return;

    glfwDefaultWindowHints();
    //OpenGL Context Settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Properties.GLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Properties.GLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, Properties.GLCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    //Window Setup
    glfwWindowHint(GLFW_DECORATED, Properties.Decorated ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, Properties.Resizeable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    Handle = glfwCreateWindow(Properties.Width, Properties.Height, Properties.Title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(Handle, this); // Two way Binding

    glfwMakeContextCurrent(Handle);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); // TODO : find a better way to load than a bulk load each time we Create a Window
    glfwSwapInterval(Properties.VSync ? GLFW_TRUE : GLFW_FALSE);
    
    LOG_INFO("OpenGL Context Info \n"
    "\tVendor   : {0}"      "\tRenderer : {1}"        "\tVersion  : {2}",
    glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

    int MonitorXOffset, MonitorYOffset;
    GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* CurrentVideoMode = glfwGetVideoMode(PrimaryMonitor);
    glfwGetMonitorPos(PrimaryMonitor, &MonitorXOffset, &MonitorYOffset);

    int WindowXOffset = MonitorXOffset + (CurrentVideoMode->width - Properties.Width) / 2;
    int WindowYOffset = MonitorYOffset + (CurrentVideoMode->height - Properties.Height) / 2;
    glfwSetWindowPos(Handle, WindowXOffset, WindowYOffset);

    //TODO : Setup Window Callbacks

    glfwShowWindow(Handle);
}

void Window::CloseImpl()
{
    if (Opened || Handle == nullptr)
        return;
    
    glfwDestroyWindow(Handle);
    Handle = nullptr;
    Opened = false;
}

/*
void OnWindowMoved(GLFWwindow* window, int x, int y)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);
    WindowMovedEvent event = WindowMovedEvent(x, y);
    w->eventSystem.dispatch(event);
}

void OnWindowResized(GLFWwindow* window, int width, int height)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);
    w->width = width;
    w->height = height;

    WindowResizedEvent event = WindowResizedEvent(width, height);
    w->eventSystem.dispatch(event);
}

void OnWindowFocus(GLFWwindow* window, int focus)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);
    if (focus)
    {
        WindowGainedFocusEvent event = WindowGainedFocusEvent();
        w->eventSystem.dispatch(event);
    }
    else
    {
        WindowLostFocusEvent event = WindowLostFocusEvent();
        w->eventSystem.dispatch(event);
    }
}

void OnWindowClosed(GLFWwindow* window)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    WindowClosedEvent event = WindowClosedEvent();
    w->eventSystem.dispatch(event);
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    switch (action)
    {
        case GLFW_REPEAT:
        case GLFW_PRESS:
        {
            w->input.setKeyPressed(key, true);
            KeyPressedEvent event = KeyPressedEvent(key);
            w->eventSystem.dispatch(event);
        }
        break;

        case GLFW_RELEASE:
        {
            w->input.setKeyPressed(key, false);
            KeyReleasedEvent event = KeyReleasedEvent(key);
            w->eventSystem.dispatch(event);
        }
        break;
    }
}

void OnChar(GLFWwindow* window, unsigned int codepoint)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    KeyTypedEvent event = KeyTypedEvent(codepoint);
    w->eventSystem.dispatch(event);
}

void OnMouseMoved(GLFWwindow* window, double x, double y)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    w->input.setMousePosition(x, y);
    MouseMovedEvent event = MouseMovedEvent(x, y);
    w->eventSystem.dispatch(event);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    switch (action)
    {
        case GLFW_REPEAT:
        case GLFW_PRESS:
        {
            w->input.setButtonPressed(button, true);
            MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
            w->eventSystem.dispatch(event);
        }
        break;

        case GLFW_RELEASE:
        {
            w->input.setButtonPressed(button, false);
            MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
            w->eventSystem.dispatch(event);
        }
        break;
    }
}

void OnMouseScrolled(GLFWwindow* window, double xOffset, double yOffset)
{
    Window* w = (Window*) glfwGetWindowUserPointer(window);

    MouseScrolledEvent event = MouseScrolledEvent(xOffset, yOffset);
    w->eventSystem.dispatch(event);
}
*/