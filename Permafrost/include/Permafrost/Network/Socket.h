#pragma once

#include "Permafrost/Core/CommonTypes.h"

class Socket
{
public:
    Socket();
    
    void Wrap(void* HandleToWrap);
    void Bind(const std::string& LocalAddress, u32 Port);
    void Connect(const std::string& RemoteAddres, u32 Port);
    void Close();

    Ref<Socket> Accept();
    void Send(const u8* Buffer, u32 Size);
    u32 Receive(u8* Buffer, u32 Size);

    inline const std::string& GetRemoteAddress() const { return RemoteAddress; }
    inline u32 GetRemotePort() const { return RemotePort; }
    inline const std::string& GetLocalAddress() const { return LocalAddress; }
    inline u32 GetLocalPort() const { return LocalPort; }

private:
    void UpdateSocketInfo();

    bool        ServerSocket;
    void*       Handle;
    std::string LocalAddress;
    u32         LocalPort;
    std::string RemoteAddress;
    u32         RemotePort;
};