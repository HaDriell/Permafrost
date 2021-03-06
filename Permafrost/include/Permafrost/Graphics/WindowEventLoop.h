#pragma once

#include <mutex>
#include <thread>

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Graphics/Window.h"

class WindowEventLoop
{
public:
    void Register(Ref<Window> WindowPtr);

    void ExecuteMainLoop();
private:
    bool IsAnyWindowOpen();
    void UpdateManagedWindows();

private:
    //List of Managed Windows
    std::mutex                  ManagedWindowsAccess;
    std::vector<Ref<Window>>    ManagedWindows;
    
public:
    static Scope<WindowEventLoop>& Get();
private:
    static Scope<WindowEventLoop> Instance;
};