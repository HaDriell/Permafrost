#include "Permafrost/Network/Network.h"

#include "Permafrost/Core/CommonTypes.h"

//Windows Specific
#include <WinSock2.h>
WSADATA __WSAData;



Scope<Network> Network::Instance;

Network::Network()
{
	WSAStartup(MAKEWORD(2, 0), &__WSAData);
}

Network::~Network()
{
	WSACleanup();
}


Ref<Socket> Network::NewSocket()
{
    return CreateRef<Socket>();
}


Scope<Network>& Network::Get()
{
    if (!Instance)
    {
        Instance.reset(new Network());
    }
    return Instance;
}