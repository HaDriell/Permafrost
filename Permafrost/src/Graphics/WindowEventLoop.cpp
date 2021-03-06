#include "Permafrost/Graphics/WindowEventLoop.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Core/Log.h"

Scope<WindowEventLoop> WindowEventLoop::Instance;

void OnGLFWErrorCallback(int error, const char* description)
{
    LOG_ERROR("[GLFW Error {0}] {1}", error, description);
}

Scope<WindowEventLoop>& WindowEventLoop::Get()
{
    if (!Instance)
    {
        Instance.reset(new WindowEventLoop());
    }
    return Instance;
}

void WindowEventLoop::Register(Ref<Window> WindowPtr)
{
    ManagedWindowsAccess.lock();
    ManagedWindows.push_back(WindowPtr);
    ManagedWindowsAccess.unlock();
}

void WindowEventLoop::ExecuteMainLoop()
{
    if (glfwInit())
    {
        glfwSetErrorCallback(&OnGLFWErrorCallback);
        do {
            glfwPollEvents();
            UpdateManagedWindows();
        } while (IsAnyWindowOpen());
        glfwTerminate();
    }
}

bool WindowEventLoop::IsAnyWindowOpen()
{
    bool AnyWindowOpen = false;

    ManagedWindowsAccess.lock();
    for (auto Window : ManagedWindows)
    {
        if (Window->Handle != nullptr)
        {
            AnyWindowOpen = true; 
            break;
        }
    }
    ManagedWindowsAccess.unlock();

    return AnyWindowOpen;
}

void WindowEventLoop::UpdateManagedWindows()
{
    std::vector<Ref<Window>> ClosedWindows;

    ManagedWindowsAccess.lock();
    for (auto Window : ManagedWindows)
    {
        //Open new Windows
        if (Window->Handle == nullptr)
        {
            Window->OpenImpl();
        }

        //Render Opened Windows
        else if (Window->Handle != nullptr)
        {
            Window->RenderImpl();
        }

        //Remove Closing Windows
        if (glfwWindowShouldClose(Window->Handle))
        {
            Window->CloseImpl();
            ClosedWindows.push_back(Window);
        }
    }

    for (auto Window : ClosedWindows)
    {
        auto It = std::find(ManagedWindows.begin(), ManagedWindows.end(), Window);
        if (It != ManagedWindows.end())
        {
            ManagedWindows.erase(It);
        }
    }
    ManagedWindowsAccess.unlock();
}