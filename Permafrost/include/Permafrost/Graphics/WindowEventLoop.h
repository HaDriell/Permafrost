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
    void Register(std::shared_ptr<Window> WindowPtr);

    void ExecuteMainLoop();
private:
    bool IsAnyWindowOpen();
    void UpdateManagedWindows();

private:
    //List of Managed Windows
    std::mutex           ManagedWindowsAccess;
    std::vector<std::shared_ptr<Window>> ManagedWindows;
};