#include "Nodes/NodeNetwork.h"

NodeNetwork::NodeNetwork(std::string const& name) : Node(name)
{

}

void NodeNetwork::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

bool NodeNetwork::InitAsClient()
{
	m_networkType = NetworkType::CLIENT;
}

bool NodeNetwork::InitAsServer(uint16 port)
{
	m_networkType = NetworkType::SERVER;
}
