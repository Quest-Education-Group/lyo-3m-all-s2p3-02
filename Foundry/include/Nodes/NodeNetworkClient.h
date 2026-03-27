#ifndef FOUNDRY_NODENETWORK_CLIENT__H_
#define FOUNDRY_NODENETWORK_CLIENT__H_

#include <thread>

#include "Node.h"
#include "Servers/NetworkServer.h"

class NodeNetworkClient : public Node
{
public:
    //class Proxy;

    NodeNetworkClient(std::string const& name);
    ~NodeNetworkClient() override;

    virtual void OnUpdate(double delta) override;

    void ConnectTo(std::string_view address, uint16 port);

    ENetAddress const& GetServerAddress() const { return m_serverAddress; }
    void SetNetworkRate(uint16 const rate) { m_networkRate = rate; }

private:
    void EventLoop();

protected:
    bool m_threadRunning = false;
    ENetAddress m_serverAddress;
    ENetPeer* m_pServerPeer;
    uint16 m_networkRate = 500;
    std::thread m_thread;
};

#endif