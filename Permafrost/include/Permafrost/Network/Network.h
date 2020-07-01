#pragma once

#include "Permafrost/Core/CommonTypes.h"
#include "Permafrost/Network/Socket.h"

class Network
{
public:
    Network();
    ~Network();

    Ref<Socket> NewSocket();

    static Scope<Network>& Get();
private:
    static Scope<Network> Instance;
};