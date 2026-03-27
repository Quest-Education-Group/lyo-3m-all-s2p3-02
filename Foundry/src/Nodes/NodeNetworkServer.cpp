#include "Nodes/NodeNetworkServer.h"

#include "Logger.hpp"

NodeNetworkServer::~NodeNetworkServer()
{
    m_threadRunning = false;
    enet_host_destroy(NetworkServer::GetEnetHost());
}

void NodeNetworkServer::OnUpdate(double const delta)
{
    Node::OnUpdate(delta);
}

bool NodeNetworkServer::Init(uint16 const port)
{
    auto& host = NetworkServer::GetEnetHost();
    if (host) return false;

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    host = enet_host_create(&address, 32, 2, 0, 0);
    if (host == nullptr)
    {
        Logger::LogWithLevel (LogLevel::ERROR, "An error occurred while trying to create an ENet server host.\n");
        return false;
    }

    Logger::Log("Server Created");
    m_thread = std::thread(&NodeNetworkServer::EventLoop, this);
    m_thread.detach();
    m_threadRunning = true;
    return true;
}

void NodeNetworkServer::EventLoop()
{
    ENetEvent event;
    while (m_threadRunning)
    {
        ENetHost* host = NetworkServer::GetEnetHost();
        while (enet_host_service (host, &event, m_networkRate) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                Logger::Log("A new client connected from ", event.peer->address.host, ":", event.peer->address.port);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                {
                    uptr<Package> package = std::make_unique<Package>();
                    std::memcpy(package.get(), event.packet->data, event.packet->dataLength);
                    NetworkServer::ReceivePackage(package);

                    enet_packet_destroy (event.packet);
                    break;
                }
            case ENET_EVENT_TYPE_DISCONNECT:
                Logger::Log("A client just disconnected.");
            }
        }
    }
}
