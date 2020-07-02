#pragma once

#include "Permafrost/Core/Configuration.h"
#include "Permafrost/Core/Log.h"
#include "Permafrost/Graphics/WindowEventLoop.h"

void Main();

int main(int argc, char** argv)
{
    LOG_INFO("*** Starting Permafrost");

    //Load or Generate Default properties file
    if (!Configuration::Get()->Load("res/permafrost.properties"))
    {
        LOG_WARNING("No permafrost.properties Configuration file in res folder !");
    }
    //Override values using command line arguments
    Configuration::Get()->Parse(argc, argv);
    
    LOG_INFO("*** Executing Permafrost");
    Main();
    WindowEventLoop::Get()->ExecuteMainLoop();

    LOG_INFO("*** Shutting down Permafrost");
    return 0;
}