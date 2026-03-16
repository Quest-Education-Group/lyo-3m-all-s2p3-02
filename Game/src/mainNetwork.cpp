//GPC-Network.cpp :
//To be clean, even if the p1 is the host the server part and client part are separated.

#include "Servers/NetworkServer.h"
#include "Nodes/NodeNetwork.h"
#include <Debug.h>

void LaunchNodeServer() 
{
	auto serverNode = Node::CreateNode<NodeNetwork>("server");
	serverNode->InitNetworkFor(NetworkType::SERVER, 54321);
	
	// == SYNCVARS ==
	SyncVar(std::string, "Name") playerName("Player1");
	SyncVar(int, "HP") playerHp = 10;
	playerHp = 55;
	SyncVar(float, "PosX") playerPosX = 5.56f;
	SyncVar(bool, "IsDead") playerIsDead = false;


	//TODO Retirer apres les tests
	if (GetAsyncKeyState('A'))
		playerHp = 50;
	// ==============
	
	serverNode->Start();
}

void LaunchNodeClient()
{
	auto clientNode = Node::CreateNode<NodeNetwork>("client");
	clientNode->InitNetworkFor(NetworkType::CLIENT);

	// == SYNCVARS ==
	SyncVar(std::string, "Name") playerName("Player2");
	SyncVar(std::string, "MyCar") playerCar("VoitureKangou");
	SyncVar(std::string, "Letter") playerLetter("A");
	SyncVar(int, "HP") playerHp = 0;
	SyncVar(float, "PosX") playerPosX = 0;
	SyncVar(bool, "IsDead") playerIsDead = true;
	// ==============

	clientNode->ConnectTo("10.10.133.17", 54321);
	clientNode->SendMsgToServerInput();

	while (true)
	{

	}
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

	//DEBUG_WHILE_TRUE
	while (true)
	{
		NetworkServer::FlushCommands();
	}

	return 0;
}
