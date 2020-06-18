#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "Permafrost/Graphics/Window.h"

class WindowEventLoop
{
public:
    static WindowEventLoop& Get();

public:
    void Register(Window* WindowPtr);
    void Unregister(Window* WindowPtr);
    void WakeUp();
    void Wait();

private:

    void EventLoopMain();
    bool IsAnyWindowOpen();
    void UpdateManagedWindows();

private:
    //Event loop Worker
    std::mutex                  GraphicsThreadAccess;
    std::thread                 GraphicsThread;

    //List of Managed Windows
    std::mutex                  ManagedWindowsAccess;
    std::vector<Window*>        ManagedWindows;
};