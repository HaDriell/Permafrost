#pragma once

#include "Permafrost/Core/Log.h"

void Configure(int argc, char** argv);

void Main();

int main(int argc, char** argv)
{
    LOG_INFO("*** Initializing Permafrost");
    Configure(argc, argv);
    
    LOG_INFO("*** Executing Permafrost");
    Main();

    LOG_INFO("*** Shutting down Permafrost");
    return 0;
}