#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "Permafrost/Core/Module.h"
#include "Permafrost/Graphics/Window.h"

class GraphicsModule : public Module<GraphicsModule>
{
public:
    void Open(std::shared_ptr<Window> WindowPtr);

private:
    void WakeupGraphicsThread();
    void GraphicsThreadMain();

    void ManageWindows();

    std::mutex  GraphicsThreadAccess;
    std::thread GraphicsThread;
  
    std::mutex                              WindowsAccess;
    std::vector<std::shared_ptr<Window>>    Windows;
};