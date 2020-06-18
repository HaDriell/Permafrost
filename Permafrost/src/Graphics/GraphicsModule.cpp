#include "Permafrost/Graphics/GraphicsModule.h"

#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Permafrost/Core/Log.h"


void GraphicsModule::Open(std::shared_ptr<Window> WindowPtr)
{
    //Thread-safe Registration
    WindowsAccess.lock();
    Windows.push_back(WindowPtr);
    WindowsAccess.unlock();

    //Thread Wakeup (to Handle the new Registration)
    WakeupGraphicsThread();
}

void GraphicsModule::WakeupGraphicsThread()
{
    GraphicsThreadAccess.lock();
    if (GraphicsThread.joinable())
    {
        glfwPostEmptyEvent();
    }
    else
    {
        GraphicsThread = std::thread(&GraphicsModule::GraphicsThreadMain, this);
    }
    GraphicsThreadAccess.unlock();
}


void GraphicsModule::GraphicsThreadMain()
{
    if (glfwInit())
    {
        while (Windows.size() > 0)
        {
            glfwWaitEvents();
            ManageWindows();
        }
        glfwTerminate();
    }
}


void GraphicsModule::ManageWindows()
{
    std::vector<std::shared_ptr<Window>> ClosedWindows;

    WindowsAccess.lock();
    for (auto WindowPtr : Windows)
    {
        //Manage Windows That are Opening
        if (WindowPtr->Handle == nullptr)
        {
            WindowProperties& Properties = WindowPtr->Properties;

            glfwDefaultWindowHints();
            //OpenGL Context Settings
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Properties.GLVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Properties.GLVersionMinor);
            glfwWindowHint(GLFW_OPENGL_PROFILE, Properties.GLCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
            //Window Setup
            glfwWindowHint(GLFW_DECORATED, Properties.Decorated ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, Properties.Resizeable ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            WindowPtr->Handle = glfwCreateWindow(Properties.Width, Properties.Height, Properties.Title.c_str(), nullptr, nullptr);
            glfwSetWindowUserPointer(WindowPtr->Handle, this); // Two way Binding

            glfwMakeContextCurrent(WindowPtr->Handle);
            gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); // TODO : find a better way to load than a bulk load each time we Create a Window
            glfwSwapInterval(Properties.VSync ? GLFW_TRUE : GLFW_FALSE);
            
            LOG_INFO("OpenGL Context Info \n"
            "\tVendor   : {0}"
            "\tRenderer : {1}"
            "\tVersion  : {2}",
            glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

            int MonitorXOffset, MonitorYOffset;
            GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* CurrentVideoMode = glfwGetVideoMode(PrimaryMonitor);
            glfwGetMonitorPos(PrimaryMonitor, &MonitorXOffset, &MonitorYOffset);

            int WindowXOffset = MonitorXOffset + (CurrentVideoMode->width - Properties.Width) / 2;
            int WindowYOffset = MonitorYOffset + (CurrentVideoMode->height - Properties.Height) / 2;
            glfwSetWindowPos(WindowPtr->Handle, WindowXOffset, WindowYOffset);

            //TODO : Setup Window Callbacks

            glfwShowWindow(WindowPtr->Handle);
        }

        //Manage Windows That are Closing
        if (glfwWindowShouldClose(WindowPtr->Handle))
        {
            glfwDestroyWindow(WindowPtr->Handle);
            WindowPtr->Handle = nullptr;
            ClosedWindows.push_back(WindowPtr);
        }
    }
    //Clean-up Closing Windows from the Windows List
    Windows.erase(ClosedWindows.begin(), ClosedWindows.end());
    WindowsAccess.unlock();
}