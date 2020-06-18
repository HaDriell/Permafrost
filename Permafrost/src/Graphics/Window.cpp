#include "Permafrost/Graphics/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Graphics/GraphicsModule.h"

bool Window::IsOpen() const
{
    return Handle != nullptr;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(Handle);
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