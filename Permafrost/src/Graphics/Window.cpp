#include "Permafrost/Graphics/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Core/Log.h"
#include "Permafrost/Graphics/WindowEventLoop.h"

static void APIENTRY OnOpenGLDebugMessage(GLenum Source, GLenum Type, unsigned int id, GLenum Severity, GLsizei Length, const char* Message, const void* UserParam)
{
    // ignore non-significant error/warning codes
    // if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    const char* SourceString;
    const char* TypeString;
    const char* SeverityString;

    switch (Source)
    {
        case GL_DEBUG_SOURCE_API:             SourceString = "API";             break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   SourceString = "Window System";   break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: SourceString = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     SourceString = "Third Party";     break;
        case GL_DEBUG_SOURCE_APPLICATION:     SourceString = "Application";     break;
        case GL_DEBUG_SOURCE_OTHER:           SourceString = "Other";           break;
    }

    switch (Type)
    {
        case GL_DEBUG_TYPE_ERROR:               TypeString = "Error";                   break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: TypeString = "Deprecated Behaviour";    break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  TypeString = "Undefined Behaviour";     break; 
        case GL_DEBUG_TYPE_PORTABILITY:         TypeString = "Portability";             break;
        case GL_DEBUG_TYPE_PERFORMANCE:         TypeString = "Performance";             break;
        case GL_DEBUG_TYPE_MARKER:              TypeString = "Marker";                  break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          TypeString = "Push Group";              break;
        case GL_DEBUG_TYPE_POP_GROUP:           TypeString = "Pop Group";               break;
        case GL_DEBUG_TYPE_OTHER:               TypeString = "Other";                   break;
    }
    
    switch (Severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SeverityString = "High";           break;
        case GL_DEBUG_SEVERITY_MEDIUM:       SeverityString = "Medium";         break;
        case GL_DEBUG_SEVERITY_LOW:          SeverityString = "Low";            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SeverityString = "Notification";   break;
    }
    LOG_DEBUG("GL(Source:{0} Type:{1} Severity:{2}) : {3}",
        SourceString, TypeString, SeverityString, std::string(Message, Length)
    );
}


std::shared_ptr<Window> Window::Open(const WindowProperties& Properties)
{
    std::shared_ptr<Window> WindowPtr = std::make_shared<Window>();
    WindowPtr->Properties = Properties;
    WindowEventLoop::Get().Register(WindowPtr);
    return WindowPtr;
}

void Window::Close()
{
    glfwSetWindowShouldClose(Handle, GLFW_TRUE);
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
    if (Handle != nullptr)
        return;

    glfwDefaultWindowHints();
    //OpenGL Context Settings
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, Properties.GLDebug ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Properties.GLVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Properties.GLVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, Properties.GLCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    //Window Setup
    glfwWindowHint(GLFW_DECORATED, Properties.Decorated ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, Properties.Resizeable ? GLFW_TRUE : GLFW_FALSE);
    //glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    Handle = glfwCreateWindow(Properties.Width, Properties.Height, Properties.Title.c_str(), nullptr, nullptr);

    if (Handle == nullptr)
    {
        LOG_ERROR("Failed to open Window.");
        return;
    }

    glfwSetWindowUserPointer(Handle, this); // Two way Binding

    glfwMakeContextCurrent(Handle);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); // TODO : find a better way to load than a bulk load each time we Create a Window
    glfwSwapInterval(Properties.VSync ? GLFW_TRUE : GLFW_FALSE);
    glDebugMessageCallback(&OnOpenGLDebugMessage, nullptr);
    
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
    if (Handle == nullptr)
        return;
    
    glfwDestroyWindow(Handle);
    Handle = nullptr;
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