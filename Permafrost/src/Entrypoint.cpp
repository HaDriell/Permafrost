#include <vector>

#include "Permafrost/Core/Module.h"
#include "Permafrost/Core/Application.h"
#include "Permafrost/Core/Log.h"


int main(int argc, char* argv[])
{
    LOG_INFO("*** Initializing Permafrost");
    Initialize(argc, argv);

    LOG_INFO("*** Executing Permafrost");
    Main();

    LOG_INFO("*** Shutting down Permafrost");
    return EXIT_SUCCESS;
}