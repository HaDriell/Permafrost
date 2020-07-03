#include "Permafrost/Core/Configuration.h"

Scope<Options> Configuration::Instance;

Scope<Options>* Configuration::Get()
{
    if (!Instance)
    {
        Instance.reset(new Options());
    }
    return Instance;
}