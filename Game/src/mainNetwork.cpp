//GPC-Network.cpp :
//To be clean, even if the p1 is the host the server part and client part are separated.

#include "Network.h"
#include "Nodes/NodeNetwork.h"

void LaunchServer()
{
	// var sync with clients
	SyncVar(std::string, "Name") playerName("Player1");
	SyncVar(int, "HP") playerHp = 10;
	playerHp = 55;
	SyncVar(float, "PosX") playerPosX = 5.56f;
	SyncVar(bool, "IsDead") playerIsDead = false;

	// Server INIT
	Network testNetwork;

	std::string localIp = testNetwork.GetLocalIP();
	std::cout << "SERVER IP = " << localIp << std::endl;

	if (testNetwork.Init(true, 54321))
	{
		testNetwork.PrintSyncVar();
		testNetwork.ServerLoop();
		testNetwork.Close();
	}

}

void LaunchClient()
{
	// Client INIT
	Network testClient;
	if (testClient.Init())
	{
		testClient.PrintSyncVar();
		
		std::string localIp = testClient.GetLocalIP();
		std::string testIp = "10.10.42.254"; // <- test with someone IP
		int testPort = 54321;

		std::cout << "CLIENT IP = " << localIp << std::endl;
		if (testClient.ConnectingTo(testIp.c_str(), testPort))
		{
			//testClient.ClientLoop();
			if (testClient.SendMsgToServer("HI ! Im going to send you my data(client)."))
			{
				//testClient.SendSyncVar();
				testClient.SendMsgToServerA();
			}
		}
	}
}

void LaunchNodeServer() 
{
	auto serverNode = Node::CreateNode<NodeNetwork>("server");
	serverNode->SetNetworkPort(54321);
	serverNode->InitNetworkFor(NetworkType::SERVER);
	serverNode->PrintNetworkInfos();

}
void LaunchNodeClient()
{
	auto clientNode = Node::CreateNode<NodeNetwork>("client");
	clientNode->InitNetworkFor(NetworkType::CLIENT);
	clientNode->PrintNetworkInfos();

	clientNode->ConnectTo("10.10.42.254", 54321);
}

int main()
{
	// Enet INIT
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	std::cout << "Enet Program launched.\n";

	//---ChooseOne---
	//LaunchServer();
	//LaunchClient();
	//LaunchNodeServer();
	LaunchNodeClient();
	//---------------

	// Program END
	atexit(enet_deinitialize);
	return 0;
}
