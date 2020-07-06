#include "Permafrost/Network/Network.h"

#include "Permafrost/Core/CommonTypes.h"



Scope<Network> Network::Instance;

Network::Network()
{
	WSAStartup(MAKEWORD(2, 2), &WSAData);
}

Network::~Network()
{
	WSACleanup();
}

void Network::Wakeup()
{
    std::lock_guard<std::mutex> Lock(NetworkWorkerAccess);
    if (!NetworkWorker.joinable())
    {
        NetworkWorker = std::thread(&Network::Listen, this);
    }
}

void Network::Listen()
{
    while (!ServerSockets.empty() || !ClientSockets.empty())
    {
        // Synchronized copy of the current Socket Selector
        fd_set ReadSelector;
        FD_ZERO(&ReadSelector);
        {
            std::lock_guard<std::mutex> Lock(SocketsAccess);
            ReadSelector = Selector;
        }


        timeval MaxSelectDuration;
        MaxSelectDuration.tv_sec = 1;

        //Number of sockets selected
        i32 Selections = select(0, &ReadSelector, nullptr, nullptr, &MaxSelectDuration);

        //Process ServerSockets
        std::vector<SOCKET> AcceptedSockets;
        for (i32 Index = 0; Selections > 0 && Index < ServerSockets.size(); Index++)
        {
            SOCKET Server = ServerSockets[Index];

            //Look for Server Selections
            if (!FD_ISSET(Server, &ReadSelector)) continue;
            Selections--;

            //Server Selections means a new Connection is acceptable
            SOCKET Client = accept(Server, nullptr, nullptr);

            if (Client == INVALID_SOCKET) continue;
            AcceptedSockets.push_back(Client);
        }

        
        //Process ClientSockets
        for (i32 Index = 0; Selections > 0 && Index < ClientSockets.size(); Index++)
        {
            SOCKET Client = ClientSockets[Index];

            if (!FD_ISSET(Client, &ReadSelector)) continue;
            Selections--;

            
            //TODO : définir un buffer de réception à taille fixe (définie dans la Configuration)
            //recv(Client, );
        }
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