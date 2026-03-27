#include "Nodes/NodeNetworkClient.h"

#include "Logger.hpp"

NodeNetworkClient::NodeNetworkClient(std::string const& name) : Node(name)
{
	auto& host = NetworkServer::GetEnetHost();
	if (host) return;

	host = enet_host_create(nullptr, 1, 2, 0, 0);

	if (NetworkServer::GetEnetHost() == nullptr)
		Logger::LogWithLevel(LogLevel::ERROR, "An error occurred while trying to create an ENet client host");

}

NodeNetworkClient::~NodeNetworkClient()
{
	m_threadRunning = false;
	enet_host_destroy(NetworkServer::GetEnetHost());
}

void NodeNetworkClient::OnUpdate(double const delta)
{
	Node::OnUpdate(delta);
}

void NodeNetworkClient::ConnectTo(std::string_view const address, uint16 const port)
{
	enet_address_set_host(&m_serverAddress, address.data());
	m_serverAddress.port = port;

	m_pServerPeer = enet_host_connect(NetworkServer::GetEnetHost(), &m_serverAddress, 2, 0);
	if (m_pServerPeer == nullptr)
	{
		Logger::LogWithLevel(LogLevel::ERROR, "No available peers for initiating an ENet connection.");
		return;
	}

	ENetEvent event;
	// Wait up to 5 seconds for the connection attempt to succeed.
	if (enet_host_service (NetworkServer::GetEnetHost(), &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		Logger::Log("Connection to ", address, ":", port, " succeeded.");
		m_threadRunning = true;
		m_thread = std::thread(&NodeNetworkClient::EventLoop, this);
		m_thread.detach();
	}
	else
	{
		enet_peer_reset(m_pServerPeer);
		Logger::LogWithLevel(LogLevel::ERROR, "Connection to ", address, ":", port, " failed.");
	}
}

void NodeNetworkClient::EventLoop()
{
	ENetEvent event;
	while (m_threadRunning)
	{
		ENetHost* host = NetworkServer::GetEnetHost();
		while (enet_host_service (host, &event, m_networkRate) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
			{
				uptr<Package> package = std::make_unique<Package>();
				std::memcpy(package.get(), event.packet->data, event.packet->dataLength);
				NetworkServer::ReceivePackage(package);

				enet_packet_destroy (event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Log("Client is not connected anymore");
			}
		}
	}
}
