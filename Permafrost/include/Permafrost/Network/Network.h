#pragma once

#include <mutex>
#include <thread>
#include <WinSock2.h>

#include "Permafrost/Core/CommonTypes.h"


class Network
{
public:
    Network();
    ~Network();

private:
    void NetworkMain();
    void Wakeup();
    void Listen();

private:
    std::thread         NetworkWorker;

    std::mutex          SocketsAccess;
    std::vector<SOCKET> ServerSockets;
    std::vector<SOCKET> ClientSockets;

    WSADATA WSAData;



//Singleton Pattern
    static Scope<Network>& Get();
private:
    static Scope<Network> Instance;
};