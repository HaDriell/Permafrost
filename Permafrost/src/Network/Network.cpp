#include "Permafrost/Network/Network.h"

#include "Permafrost/Core/CommonTypes.h"



Scope<Network> Network::Instance;

Network::Network()
{
	WSAStartup(MAKEWORD(2, 0), &WSAData);
}

Network::~Network()
{
	WSACleanup();
}

void Network::Listen()
{
    fd_set Selector;
    FD_ZERO(&Selector);

    // Fill Selector safely
    {
        std::lock_guard<std::mutex> Lock(SocketsAccess);       
        
        for (SOCKET Server : ServerSockets)
        {
            FD_SET(Server, &Selector);
        }

        for (SOCKET Client : ClientSockets)
        {
            FD_SET(Client, &Selector);
        }
    }

    i32 Selections = select(0, &Selector, nullptr, nullptr, nullptr); 

    //Process ServerSockets
    std::vector<SOCKET> AcceptedSockets;
    for (i32 Index = 0; Selections > 0 && Index < ServerSockets.size(); Index++)
    {
        SOCKET Server = ServerSockets[Index];
        if (!FD_ISSET(Server, &Selector)) continue;

        Selections--;

        SOCKET Client = accept(Server, nullptr, nullptr);

        if (Client == INVALID_SOCKET) continue;
        AcceptedSockets.push_back(Client);
    }

    //Process ClientSockets
    for (i32 Index = 0; Selections > 0 && Index < ClientSockets.size(); Index++)
    {
        SOCKET Client = ClientSockets[Index];

        //TODO : définir un buffer de réception à taille fixe (définie dans la Configuration)
        //recv(Client, );
    }
}

Scope<Network>& Network::Get()
{
    if (!Instance)
    {
        Instance.reset(new Network());
    }
    return Instance;
}