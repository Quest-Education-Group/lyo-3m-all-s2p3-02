//GPC-Network.cpp :
//To be clean, even if the p1 is the host the server part and client part are separated.

#include "Debug.h"
#include "Servers/NetworkServer.h"
#include "Nodes/NodeNetworkServer.h"
#include "Network/SyncVar.h"
#include "Nodes/NodeNetworkClient.h"
#include "Servers/EngineServer.h"

int main(int argc, char** argv)
{
	//SyncVar(std::string, "Name") playerName("Player1");
	//SyncVar(bool, "IsDead") playerIsDead = false;


	if (argc < 2) return -1;
	NetworkServer::Initialize();

	uptr<Node> root = Node::CreateNode<Node>("Root");

	std::string argInput = std::string(argv[1]);
	if (argInput.compare("-server") == 0)
	{
		uptr<NodeNetworkServer> server = Node::CreateNode<NodeNetworkServer>("Server");
		server->Init(5563);
		root->AddChild(std::move(server));
	}
	else
	{
		uptr<NodeNetworkClient> client = Node::CreateNode<NodeNetworkClient>("Client");
		client->ConnectTo("127.0.0.1", 5563);
		root->AddChild(std::move(client));
	}

	SyncVar(float, "PosX") playerPosX = 5.56f;
	playerPosX.OnValueChange += [](float const newVal){DEBUG("New playerPosX value : " << newVal << std::endl); };

	playerPosX = 11.35f;

	std::thread input([&]()
	{
		while (true)
		{
			float newVal; std::cin >> newVal; playerPosX += newVal;
		}
	});
	input.detach();

	EngineServer::FlushCommands();
	//DEBUG_WHILE_TRUE
	while (true)
	{
		NetworkServer::FlushCommands();
	}

	NetworkServer::UnInitialize();
}
