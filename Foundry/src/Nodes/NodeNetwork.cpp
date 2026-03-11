#include "Nodes/NodeNetwork.h"

NodeNetwork::NodeNetwork(std::string const& name) : Node(name)
{

}

void NodeNetwork::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

void NodeNetwork::InitNetworkFor(NetworkType type, int port)
{
	m_network.Init(static_cast<bool>(type), port);
}

void NodeNetwork::SendMsgToServerInput()
{
	m_network.SendMsgToServerInput();
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