#include "Nodes/NodeNetwork.h"

NodeNetwork::NodeNetwork(std::string const& name) : Node(name)
{

}

void NodeNetwork::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

void NodeNetwork::CloseNetwork()
{
	m_network.Close();
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
		m_network.Init();
		break;
	default:
		break;
	}
}

void NodeNetwork::SetNetworkPort(int const addressPORT)
{
	m_network.NetworkSetPort(addressPORT);
}