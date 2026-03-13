#include "Servers/NetworkServer.h"
#include "Multithreading/TaskGraph.h"

bool NetworkServer::Init(NetworkType networkType, int serverPort)
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::INIT;
	cmd.inputType = networkType;
	cmd.inputPort = serverPort;

	Instance().m_commands.push(cmd);

	return true;
}

void NetworkServer::Start()
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::START;

	Instance().m_commands.push(cmd);
}

void NetworkServer::Close()
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::CLOSE;

	Instance().m_commands.push(cmd);
}

bool NetworkServer::ConnectingTo(const char* addressIP, int addressPort)
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::CONNECTTO;
	cmd.inputChar = addressIP;
	cmd.inputPort = addressPort;

	Instance().m_commands.push(cmd);

	return true;
}

bool NetworkServer::SendMsgToClientsInput()
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::SENDMSGCLIENTS;

	Instance().m_commands.push(cmd);

	return true;
}

bool NetworkServer::SendMsgToServerInput()
{
	Command<NetworkServer> cmd;
	cmd.Type = CommandType::SENDMSGSERVER;

	Instance().m_commands.push(cmd);

	return true;
}

void NetworkServer::Loop() 
{
	ENetEvent event;
	while (m_isRunning) 
	{
		while (enet_host_service(m_pHost, &event, 10) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				ReceiveConnection(event);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				ReceiveDisconnection(event);
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				ReceivePackage(event);
				break;
			}
			default:
				break;
			}
		}
	}
}

void NetworkServer::ReceiveConnection(ENetEvent& event)
{
	if (m_type == NetworkType::SERVER) 
	{
		std::cout << "New Client has joinned !" << std::endl;
		m_clients.push_back(event.peer);
	}
	if (m_type == NetworkType::CLIENT)
	{
		std::cout << "Succesfully connected to Enet Server !" << std::endl;
		SendMsgToServer("Hello");
	}
}

void NetworkServer::ReceiveDisconnection(ENetEvent& event)
{
	if (m_type == NetworkType::SERVER)
	{
		std::cout << "Client disconnected !" << std::endl;
		auto it = std::remove(m_clients.begin(), m_clients.end(), event.peer);
		m_clients.erase(it, m_clients.end());
	}
	if (m_type == NetworkType::CLIENT)
	{

	}
}

void NetworkServer::ReceivePackage(ENetEvent& event)
{
	if (event.packet->dataLength == sizeof(Package))
	{
		Package* package = reinterpret_cast<Package*>(event.packet->data);

		ReceiveSyncVar(package);
		//PrintSyncVar();
	}
	else
	{
		std::cout << "Received msg : " << event.packet->data << std::endl;
	}
	enet_packet_destroy(event.packet);

	if (m_type == NetworkType::SERVER)
	{
		SendMsgToClients("PackageReceived\n");
		std::thread sendResponseToClientsThread(&NetworkServer::SendMsgToClientsInput, this);
		sendResponseToClientsThread.detach();
	}
	if (m_type == NetworkType::CLIENT)
	{
		std::thread sendResponseToServThread(&NetworkServer::SendMsgToServerInput, this);
		sendResponseToServThread.detach();
	}

}

void NetworkServer::DisconnectFromServer()
{
	if (m_pServerConnection)
	{
		std::cout << "Disconnecting from " << m_pServerConnection->address.host << " | " << m_pServerConnection->address.port << "...\n";
		enet_peer_disconnect(m_pServerConnection, 0);
		//Close();
	}
}

bool NetworkServer::SendMsgToClients(const char* message)
{
	for (auto Network : m_clients)
	{
		ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(Network, 0, packet);
		enet_host_flush(m_pHost);
	}

	enet_host_flush(m_pHost);
	return true;
}

bool NetworkServer::SendMsgToServer(const char* message)
{
	ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(m_pServerConnection, 0, packet);
	enet_host_flush(m_pHost);
	return true;
}

void NetworkServer::CommandManager(std::string command)
{
	if (command[0] == '/')
	{
		if (command == "/close")
		{
			Close();
		}
		if (command == "/disconnect")
		{
			DisconnectFromServer();
		}
		if (command == "/send")
		{
			//SendSyncVar();
		}
		if (command == "/print")
		{
			PrintSyncVar();
		}
		if (command == "/value")
		{
			PrintSyncVarValues();
		}
	}
}

void NetworkServer::PrinNetworkInfos()
{

	std::cout << "\n---[Network Type: " << TypeToStr() << "]---" << std::endl;
	std::cout << "PORT: " << m_address.port << std::endl;
	std::cout << "HOST: " << m_address.host << " (0 == Listen everyone)" << std::endl;
	std::cout << "IP  : " << GetLocalIP() << std::endl;
	std::cout << "----------------------------\n" << std::endl;
}

void NetworkServer::ReceiveSyncVar(Package* package)
{
	std::cout << "Receiving syncVars..." << std::endl;

	auto& registry = SyncRegistry::Instance().Get();

	auto it = registry.find(package->name);
	if (it != registry.end())
	{
		std::memcpy(it->second.data, package->data, package->size);

		std::cout << "Received pkg: " << package->name << " size=" << package->size << std::endl;
	}
	else
	{
		std::cout << "SyncVar not found: " << package->name << std::endl;
	}
}

void NetworkServer::SendSyncVar(std::string const& name)
{
	auto& registry = SyncRegistry::Instance().Get();


	auto& entry = registry[name];
	//for (auto& [name, entry] : registry)
	{
		std::cout << "Sending SyncVars." << std::endl;

		Package pkg{};

		// name
		//strcpy_s(pkg.name, name.c_str());
		// size
		pkg.size = entry.size;
		// data
		std::memcpy(pkg.data, entry.data, entry.size);

		if (m_type == NetworkType::SERVER) 
		{
			for (auto client : m_clients)
			{
				// packet enet
				ENetPacket* packet = enet_packet_create(&pkg, sizeof(Package), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(client, 0, packet);
				enet_host_flush(m_pHost);
			}
		}

		if (m_type == NetworkType::CLIENT) 
		{
			// packet enet
			ENetPacket* packet = enet_packet_create(&pkg, sizeof(Package), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(m_pServerConnection, 0, packet);
			enet_host_flush(m_pHost);
		}

	}
}

void NetworkServer::PrintSyncVar()
{
	std::cout << "---SyncVars---\n";

	auto& registry = SyncRegistry::Instance().Get();

	if (registry.empty())
	{
		std::cout << "[ShowSyncVars] registry empty!\n";
	}

	for (auto& syncVar : registry)
	{
		std::string name = syncVar.first;
		const Package& entry = syncVar.second;

		std::cout << name.c_str() << " size=" << entry.size << std::endl;
	}

	std::cout << "------------" << std::endl;
}

void NetworkServer::PrintSyncVarValues()
{
	std::cout << "---SyncVar Values---\n";
	
	auto& registry = SyncRegistry::Instance().Get();

	for (auto& [name, entry] : registry)
	{
		std::cout << name << " = ";

		if (entry.size == sizeof(int))
		{
			int v; 
			std::memcpy(&v, entry.data, sizeof(int));
			std::cout << v;
		}
		else if (entry.size == sizeof(float))
		{
			float v; 
			std::memcpy(&v, entry.data, sizeof(float));
			std::cout << v;
		}
		else if (entry.size == sizeof(bool))
		{
			bool v;
			std::memcpy(&v, entry.data, sizeof(bool));
			if (v) 
			{
				std::cout << "TRUE";
			}
			else
			{
				std::cout << "FALSE";
			}
			
		}
		else if (entry.size == sizeof(char))
		{
			std::cout << entry.data[0];
		}
		else if (entry.size == sizeof(std::string))
		{
			std::string value(reinterpret_cast<char*>(entry.data) + 5, entry.size);
			std::cout << value;
		}
		else
		{
			std::cout << "TypeError";
		}

		std::cout << "\n";
	}

	std::cout << "--------------------\n";
}

std::string NetworkServer::GetLocalIP() const
{
	char hostname[256];
	gethostname(hostname, sizeof(hostname));

	addrinfo hints = {};
	hints.ai_family = AF_INET;

	addrinfo* result = nullptr;
	getaddrinfo(hostname, NULL, &hints, &result);

	char ip[INET_ADDRSTRLEN] = { 0 };

	sockaddr_in* sockaddr_ipv4 = (sockaddr_in*)result->ai_addr;
	inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ip, sizeof(ip));

	freeaddrinfo(result);

	return std::string(ip);
}

std::string NetworkServer::TypeToStr() const 
{
	std::string typeStr;

	switch (m_type)
	{
	case NetworkType::CLIENT:
		typeStr = "CLIENT";
		break;
	case NetworkType::SERVER:
		typeStr = "SERVER";
		break;
	case NetworkType::NOT_DEFINED:
		typeStr = "NOT_DEFINED";
		break;
	default:
		break;
	}

	return typeStr;
}

NetworkAdress NetworkServer::GetAddress() const
{
	return m_address;
}

bool NetworkServer::GetIsRunning() const 
{
	return m_isRunning;
}

NetworkType NetworkServer::GetType() const
{
	return m_type;
}

bool NetworkServer::StartEnet() 
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return false;
	}
	else
	{
		std::cout << "Enet Program launched.\n";
		return true;
	}
}

void NetworkServer::StopEnet() 
{
	std::cout << "Enet Program stopping.\n";
	//atexit(enet_deinitialize);
	enet_deinitialize();
}

void NetworkServer::BuildTasksImpl(TaskGraph& graph)
{
	//uptr<Task> t = std::make_unique<Task>();
	//t->TaskFunction = [this] { SendMsgToServer("test"); };
	//t->Name = "SendMsgToServer";
	//graph.AddTask(t);
}

void NetworkServer::FlushCommandsImpl()
{
	while (m_commands.empty() == false)
	{
		Command<NetworkServer>& command = m_commands.front();

		switch (command.Type)
		{
		case CommandType::INIT:
			Command_Init(command.inputType, command.inputPort);
			m_commands.pop();
			break;
		case CommandType::START:
			Command_Start();
			m_commands.pop();
			break;
		case CommandType::CONNECTTO:
			Command_ConnectingTo(command.inputChar, command.inputPort);
			m_commands.pop();
			break;
		case CommandType::SENDMSGCLIENTS:
			Command_SendMsgToClientsInput();
			m_commands.pop();
			break;
		case CommandType::SENDMSGSERVER:
			Command_SendMsgToServerInput();
			m_commands.pop();
			break;
		case CommandType::PRINTINFO:
			PrinNetworkInfos();
			m_commands.pop();
			break;
		case CommandType::CLOSE:
			Command_Close();
			m_commands.pop();
			break;
		}
	}
}

bool NetworkServer::Command_Init(NetworkType networkType, int serverPort)
{
	auto& inst = Instance();
	inst.m_type = networkType;

	switch (inst.m_type)
	{
	case NetworkType::CLIENT:
	{
		inst.m_pHost = enet_host_create(NULL, 1, 2, 0, 0);

		inst.PrinNetworkInfos();
	}
	break;
	case NetworkType::SERVER:
	{
		inst.m_address.host = ENET_HOST_ANY;
		inst.m_address.port = serverPort;

		//server
		ENetAddress enetAddress;
		enetAddress.host = inst.m_address.host;
		enetAddress.port = inst.m_address.port;

		inst.m_pHost = enet_host_create(&enetAddress, 32, 2, 0, 0);

		inst.PrinNetworkInfos();
	}
	break;
	case NetworkType::NOT_DEFINED:
	{
		std::cout << "Network haven't been defined [!]" << std::endl;
	}
	break;
	default:
		break;
	}

	if (inst.m_pHost == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
		return false;
	}

	return true;
}

bool NetworkServer::Command_Start() 
{
	auto& inst = Instance();

	std::cout << "Starting network...\n";
	inst.m_isRunning = true;
	Loop();
}

void NetworkServer::Command_Close()
{
	auto& inst = Instance();

	if (inst.m_pHost != NULL)
	{
		std::cout << "Closing session...\n";
		inst.m_isRunning = false;
		enet_host_destroy(inst.m_pHost);
	}
}

bool NetworkServer::Command_ConnectingTo(const char* addressIP, int addressPort)
{
	auto& inst = Instance();

	std::cout << "Trying connection to " << addressIP << " | " << addressPort << std::endl;

	ENetAddress enetAddress;
	enet_address_set_host(&enetAddress, addressIP);
	enetAddress.port = addressPort;

	inst.m_pServerConnection = enet_host_connect(inst.m_pHost, &enetAddress, 2, 0);
	if (!inst.m_pServerConnection)
	{
		std::cerr << "Connection failed to server." << std::endl;
		enet_host_destroy(inst.m_pHost);
		return false;
	}
	else
	{
		std::cout << "Connecting..." << std::endl;
		inst.m_isRunning = true;
	}

	// Thread background
	//std::thread clientLoopThread(&NetworkServer::Loop, inst); <- a tester
	std::thread clientLoopThread(&NetworkServer::Loop, this);
	clientLoopThread.detach();

	return true;
}

bool NetworkServer::Command_SendMsgToClientsInput()
{
	std::string msg;
	std::cin >> msg;

	CommandManager(msg);

	for (auto Network : m_clients)
	{
		ENetPacket* packet = enet_packet_create(msg.c_str(), strlen(msg.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(Network, 0, packet);
		enet_host_flush(m_pHost);
	}

	enet_host_flush(m_pHost);
	return true;
}

bool NetworkServer::Command_SendMsgToServerInput()
{
	std::cout << "Enter msg: "; //should be removed
	std::string msg;
	std::cin >> msg;

	CommandManager(msg);

	ENetPacket* packet = enet_packet_create(msg.c_str(), strlen(msg.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(m_pServerConnection, 0, packet);
	enet_host_flush(m_pHost);

	return true;
}