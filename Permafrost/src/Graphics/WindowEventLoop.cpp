#include "Permafrost/Graphics/WindowEventLoop.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Core/Log.h"

static WindowEventLoop EventLoop;

WindowEventLoop& WindowEventLoop::Get()
{
    return EventLoop;
}

void WindowEventLoop::Register(Window* WindowPtr)
{
    ManagedWindowsAccess.lock();
    ManagedWindows.push_back(WindowPtr);
    ManagedWindowsAccess.unlock();
}

void WindowEventLoop::Unregister(Window* WindowPtr)
{
    ManagedWindowsAccess.lock();
    auto It = std::find(ManagedWindows.begin(), ManagedWindows.end(), WindowPtr);

    if (It != ManagedWindows.end())
    {
        ManagedWindows.erase(It);

        if (WindowPtr->Handle != nullptr)
        {
            glfwDestroyWindow(WindowPtr->Handle);
            WindowPtr->Handle = nullptr;
            WindowPtr->Opened = false;
        }
    }

    ManagedWindowsAccess.unlock();
}

void WindowEventLoop::WakeUp()
{
    GraphicsThreadAccess.lock();
    if (GraphicsThread.joinable())
    {
        glfwPostEmptyEvent();
    }
    else
    {
        GraphicsThread = std::thread(&WindowEventLoop::EventLoopMain, this);
    }
    GraphicsThreadAccess.unlock();
}

void WindowEventLoop::Wait()
{
    if (GraphicsThread.joinable())
    {
        GraphicsThread.join();
    }
}

void WindowEventLoop::EventLoopMain()
{
    LOG_INFO("Initializing Event Loop");
    if (glfwInit())
    {
        LOG_INFO("Starting Event Loop");
        while (IsAnyWindowOpen())
        {
            glfwWaitEvents();
            UpdateManagedWindows();
        }

        LOG_INFO("Terminating Event Loop");
        //GLFW Dangling Pointer
        ManagedWindowsAccess.lock();
        for (auto* Window : ManagedWindows)
        {
            Window->Handle = nullptr;
        }
        ManagedWindowsAccess.unlock();
        glfwTerminate();
    }
    LOG_INFO("Exiting Event Loop");
}

bool WindowEventLoop::IsAnyWindowOpen()
{
    bool AnyWindowOpen = false;

    ManagedWindowsAccess.lock();
    for (auto* Window : ManagedWindows)
    {
        if (Window->Opened)
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
    ManagedWindowsAccess.lock();
    for (auto* Window : ManagedWindows)
    {
        //Detect Opening Request
        if (Window->Opened && Window->Handle == nullptr)
        {
            Window->OpenImpl();
        }

        //Detect Close Request
        if (!Window->Opened && Window->Handle != nullptr)
        {
            Window->CloseImpl();
        }
    }
    ManagedWindowsAccess.unlock();
}