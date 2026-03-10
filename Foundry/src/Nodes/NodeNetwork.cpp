#include "Nodes/NodeNetwork.h"

NodeNetwork::NodeNetwork(std::string const& name) : Node(name)
{

}

void NodeNetwork::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

void NodeNetwork::InitNetworkFor(NetworkType type) 
{
	switch (type)
	{
	case NetworkType::SERVER:
		if (m_network.Init(true))
		{
			m_network.ServerLoop();
		}
		break;
	case NetworkType::CLIENT:
		m_network.Init(false);
		break;
	default:
		break;
	}
}

void NodeNetwork::SendMsgToServer(const char* message)
{
	m_network.SendMsgToServer(message);
}

void NodeNetwork::SendMsgToClients(const char* message)
{
	m_network.SendMsgToClients(message);
}

void NodeNetwork::ConnectTo(const char* addressIP, int addressPort) 
{
	m_network.ConnectingTo(addressIP, addressPort);
}

void NodeNetwork::PrintNetworkInfos()
{
	m_network.PrinNetworkInfos();
}

void NodeNetwork::CloseNetwork()
{
	m_network.Close();
}

void NodeNetwork::SetNetworkPort(int const addressPORT)
{
	m_network.NetworkSetPort(addressPORT);
}