//GPC-Network.cpp :
//To be clean, even if the p1 is the host the server part and client part are separated.

#include "Servers/NetworkServer.h"
#include "Nodes/NodeNetwork.h"

void TestSyncVar()
{
	// var sync with clients
	SyncVar(std::string, "Name") playerName("Player1");
	SyncVar(int, "HP") playerHp = 10;
	playerHp = 55;
	SyncVar(float, "PosX") playerPosX = 5.56f;
	SyncVar(bool, "IsDead") playerIsDead = false;
}

void LaunchNodeServer() 
{
	auto serverNode = Node::CreateNode<NodeNetwork>("server");
	serverNode->InitNetworkFor(NetworkType::SERVER, 54321);
}
void LaunchNodeClient()
{
	auto clientNode = Node::CreateNode<NodeNetwork>("client");
	clientNode->InitNetworkFor(NetworkType::CLIENT);

	clientNode->ConnectTo("10.10.133.17", 54321);
	clientNode->SendMsgToServerInput();
}


int main(int argc, char** argv)
{
	if (NetworkServer::StartEnet())
	{
		if (argc > 1)
		{
			std::string argInput = std::string(argv[1]);

			if (argInput == "-server")
			{
				LaunchNodeServer();
			}
			if (argInput == "-client")
			{
				LaunchNodeClient();
			}
		}
		else
		{
			LaunchNodeServer();
		}
	}

	NetworkServer::StopEnet();

	return 0;
}
