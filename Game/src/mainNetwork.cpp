//GPC-Network.cpp :
//To be clean, even if the p1 is the host the server part and client part are separated.

#include "Servers/NetworkServer.h"
#include "Nodes/NodeNetwork.h"
#include <Debug.h>

void LaunchNodeServer() 
{
	auto serverNode = Node::CreateNode<NodeNetwork>("server");
	serverNode->InitNetworkFor(NetworkType::SERVER, 54321);

	//TODO Retirer apres les tests
	//if (GetAsyncKeyState('A'))
	//	playerHp = 50;
	// ==============
	
	serverNode->Start();
}

void LaunchNodeClient()
{
	auto clientNode = Node::CreateNode<NodeNetwork>("client");
	clientNode->InitNetworkFor(NetworkType::CLIENT);
	clientNode->ConnectTo("127.0.0.1", 54321); //Adresse local
	//clientNode->ConnectTo("192.168.1.6", 54321);
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
			//LaunchNodeClient();
		}
	}

	// == SYNCVARS ==
	SyncVar(std::string, "Name") playerName("Player2");
	SyncVar(std::string, "MyCar") playerCar("VoitureKangou");
	SyncVar(std::string, "Letter") playerLetter("A");
	SyncVar(int, "HP") playerHp = 0;
	SyncVar(float, "PosX") playerPosX = 0;
	SyncVar(bool, "IsDead") playerIsDead = true;
	// ==============

	while (true)
	{
		NetworkServer::FlushCommands();
	}

	NetworkServer::StopEnet();

	return 0;
}
