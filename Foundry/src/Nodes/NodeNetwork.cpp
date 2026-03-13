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
	NetworkServer::Init(type, port);
	//m_network.Init(type, port);
}

void NodeNetwork::Start()
{
	//m_network.Start();
	NetworkServer::Start();
}

void NodeNetwork::SendMsgToServerInput()
{
	//m_network.SendMsgToServerInput();
	NetworkServer::SendMsgToServerInput();
}

void NodeNetwork::ConnectTo(const char* addressIP, int addressPort) 
{
	//m_network.ConnectingTo(addressIP, addressPort);
	NetworkServer::ConnectingTo(addressIP, addressPort);
}

void NodeNetwork::CloseNetwork()
{
	//m_network.Close();
	NetworkServer::Close();
}