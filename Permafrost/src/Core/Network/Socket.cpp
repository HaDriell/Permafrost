#include "Permafrost/Network/Socket.h"

#include "Permafrost/Core/Log.h"
#include "Permafrost/Network/Network.h"

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

Socket::Socket()
    : Handle(nullptr)
{
}

void Socket::Wrap(void* HandleToWrap)
{
    assert(Handle == nullptr);

    this->Handle = HandleToWrap;

    UpdateSocketInfo();
}

void Socket::Bind(const std::string& Address, u32 Port)
{
    assert(Handle == nullptr);

    SOCKET Socket   = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN Data;
    Data.sin_family = AF_INET;
    Data.sin_port   = htons(Port);

    bind(Socket, (SOCKADDR*) &Data, sizeof(SOCKADDR_IN));
    listen(Socket, 0);

    Handle          = (void*) Socket;
    ServerSocket    = true;

    UpdateSocketInfo();
}

void Socket::Connect(const std::string& Address, u32 Port)
{
    assert(Handle == nullptr);

    SOCKET Socket   = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN Data;
    Data.sin_addr.s_addr = inet_addr(Address.c_str());
    Data.sin_family      = AF_INET;
    Data.sin_port        = htons(Port);

    connect(Socket, (SOCKADDR*) &Data, sizeof(SOCKADDR_IN));
    Handle          = (void*) Socket;
    ServerSocket    = false;

    UpdateSocketInfo();
}

void Socket::Close()
{
    assert(Handle != nullptr);

    closesocket((SOCKET) Handle);
    Handle = nullptr;

    UpdateSocketInfo();
}

Ref<Socket> Socket::Accept()
{
    SOCKADDR_IN Options;
    Options.sin_family  = AF_INET;
    Options.sin_port    = htons(LocalPort); 
    int OptionsSize = sizeof(Options);

    SOCKET ClientSocket = INVALID_SOCKET;
    while (ClientSocket == INVALID_SOCKET)
    {
        ClientSocket = accept((SOCKET) Handle, (SOCKADDR*) &Options, &OptionsSize);
    }

    Ref<Socket> Client = Network::Get()->NewSocket();
    Client->Wrap((void*) ClientSocket);
    return Client;
}

void Socket::Send(const u8* Buffer, u32 Size)
{
    send((SOCKET) Handle, (const char *) Buffer, Size, 0);
}

u32 Socket::Receive(u8* ReadBuffer, u32 Size)
{
    return recv((SOCKET) Handle, (char *) ReadBuffer, Size, 0);
}

void Socket::UpdateSocketInfo()
{
    if (!Handle)
    {
        LocalAddress    = "0.0.0.0";
        LocalPort       = 0;
        RemoteAddress   = "0.0.0.0";
        RemotePort      = 0;
        return;
    }

    SOCKADDR_IN Data;
    int Length;
    
    //Fetch Local Socket Data
    Data    = {0};
    Length  = sizeof(Data);
    getsockname((SOCKET) Handle, (SOCKADDR*) &Data, &Length);
    LocalAddress    = std::string(inet_ntoa(Data.sin_addr));
    LocalPort       = ntohs(Data.sin_port);

    //Fetch Remote Socket Data
    Data    = {0};
    Length  = sizeof(Data);
    getpeername((SOCKET) Handle, (SOCKADDR*) &Data, &Length);
    RemoteAddress   = std::string(inet_ntoa(Data.sin_addr));
    RemotePort      = ntohs(Data.sin_port);
}