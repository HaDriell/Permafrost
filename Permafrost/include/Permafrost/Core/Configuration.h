#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Core/Options.h"


#pragma region Constants

#define PERMAFROST_IMPLEMENT_OPTIONS

#ifdef PERMAFROST_IMPLEMENT_OPTIONS
    #define PERMAFROST_CONSTANT(ConstantName, ConstantKey, ConstantDefault) \
        const std::string ConstantName           =  (ConstantKey);          \
        const std::string DEFAULT_##ConstantName =  #ConstantDefault;       \
    //PERMAFROST_CONSTANT end
#else
    #define PERMAFROST_CONSTANT(ConstantName, ConstantKey, ConstantDefault) \
        const std::string ConstantName;                                     \
        const std::string DEFAULT_##ConstantName;                           \
    //PERMAFROST_CONSTANT end
#endif

PERMAFROST_CONSTANT( NETWORK_BUFFER_SIZE , "network.buffer.size" , 4096 )

#pragma endregion Constants


class Configuration
{
public:
    static Scope<Options>* Get();

private:
    static Scope<Options> Instance;
};