#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Options.h"

class Configuration
{
public:
    static Scope<Options>& Get();

private:
    static Scope<Options> Instance;
};