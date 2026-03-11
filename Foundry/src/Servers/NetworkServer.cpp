#include "Servers/NetworkServer.h"
#include "Multithreading/TaskGraph.h"

bool NetworkServer::Init(bool isServer, int serverPort)
{
	m_isServer = isServer;

	if (m_isServer == true)
	{
		m_address.host = ENET_HOST_ANY;
		m_address.port = serverPort;

		//server
		ENetAddress enetAddress;
		enetAddress.host = m_address.host;
		enetAddress.port = m_address.port;

		m_pHost = enet_host_create(&enetAddress, 32, 2, 0, 0);

		PrinNetworkInfos();

		m_isRunning = true;
		Loop();
	}
	if (m_isServer == false)
	{
		m_pHost = enet_host_create(NULL, 1, 2, 0, 0);

		PrinNetworkInfos();
	}

	if (m_pHost == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
		return false;
	}

	return true;
}

void NetworkServer::Close()
{
	if (m_pHost != NULL)
	{
		std::cout << "Closing session...\n";
		if (m_isServer) m_isRunning = false;
		enet_host_destroy(m_pHost);
	}
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
	if (m_isServer == true) 
	{
		std::cout << "New Client has joinned !" << std::endl;
		m_clients.push_back(event.peer);
	}
	if (m_isServer == false) 
	{
		std::cout << "Succesfully connected to Enet Server !" << std::endl;
		SendMsgToServer("Hello");
	}
}

void NetworkServer::ReceiveDisconnection(ENetEvent& event)
{
	if (m_isServer == true) 
	{
		std::cout << "Client disconnected !" << std::endl;
		auto it = std::remove(m_clients.begin(), m_clients.end(), event.peer);
		m_clients.erase(it, m_clients.end());
	}
	if (m_isServer == false) 
	{

	}
}

void NetworkServer::ReceivePackage(ENetEvent& event)
{
	if (event.packet->dataLength == sizeof(Package))
	{
		Package* package = reinterpret_cast<Package*>(event.packet->data);

		ReceiveSyncVar(package);
		PrintSyncVar();
	}
	else
	{
		std::cout << "Received msg : " << event.packet->data << std::endl;
	}
	enet_packet_destroy(event.packet);

	if (m_isServer == true) 
	{

	}
	if (m_isServer == false) 
	{

	}
}

bool NetworkServer::ConnectingTo(const char* addressIP, int addressPort)
{
	std::cout << "Trying connection to " << addressIP << " | " << addressPort << std::endl;

	ENetAddress enetAddress;
	enet_address_set_host(&enetAddress, addressIP);
	enetAddress.port = addressPort;

	m_pServerConnection = enet_host_connect(m_pHost, &enetAddress, 2, 0);
	if (!m_pServerConnection)
	{
		std::cerr << "Connection failed to server." << std::endl;
		enet_host_destroy(m_pHost);
		return false;
	}
	else
	{
		std::cout << "Connecting..." << std::endl;
		m_isRunning = true;
	}

	// Thread background
	std::thread clientLoopThread(&NetworkServer::Loop, this);
	clientLoopThread.detach();

	return true;
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

bool NetworkServer::SendMsgToServerInput()
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
		if (command == "/sendToServ")
		{
			SendSyncVar();
		}
	}
}

void NetworkServer::PrinNetworkInfos()
{
	std::cout << "\n---[Network Type: " << (m_isServer ? "SERVER" : "CLIENT") << "]---" << std::endl;
	std::cout << "PORT: " << m_address.port << std::endl;
	std::cout << "HOST: " << m_address.host << " (0 == Listen everyone)" << std::endl;
	std::cout << "IP  : " << GetLocalIP() << std::endl;
	std::cout << "----------------------------\n" << std::endl;
}

void NetworkServer::ReceiveSyncVar(Package* package)
{
	std::cout << "Receiving syncVars..." << std::endl;
	auto& registry = SyncRegistry::Instance().Get();

	std::memcpy(registry[package->name].data, package->data, package->size);

	std::cout << "Received pkg: " << package->name << " size=" << package->size << std::endl;
}

void NetworkServer::SendSyncVar()
{
	auto& registry = SyncRegistry::Instance().Get();

	for (auto& [name, entry] : registry)
	{
		Package pkg{};

		/*std::memset(pkg.name, 0, sizeof(pkg.name));
		size_t nameLen = name.size();
		if (nameLen > sizeof(pkg.name) - 1)nameLen = sizeof(pkg.name) - 1;
		std::memcpy(pkg.name, name.c_str(), nameLen);

		if (entry.type == SyncType::STRING)
		{
			std::string* s = static_cast<std::string*>(entry.data);
			size_t dataLen = s->size();

			if (dataLen > sizeof(pkg.data))dataLen = sizeof(pkg.data);

			pkg.dataSize = (int)dataLen;
			pkg.type = entry.type;
			std::memcpy(pkg.data, s->c_str(), dataLen);
		}
		else
		{
			size_t sendSize = entry.size;

			if (sendSize > sizeof(pkg.data))sendSize = sizeof(pkg.data);

			pkg.dataSize = (int)sendSize;
			pkg.type = entry.type;
			std::memcpy(pkg.data, entry.data, sendSize);
		}

		ENetPacket* packet = enet_packet_create(&pkg, sizeof(pkg), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(m_pServerConnection, 0, packet);
		std::cout << "Server" << m_pServerConnection->connectID << " (syncing vars...)" << std::endl;*/
	}

	enet_host_flush(m_pHost);
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

		std::cout << name.c_str() << ": ";
		//switch (entry.type)
		//{
		//case SyncType::INT:
		//{
		//	std::cout << "INT=";
		//	std::cout << std::to_string(*static_cast<int*>(entry.data)).c_str();
		//	break;
		//}
		//case SyncType::FLOAT:
		//{
		//	std::cout << "FLOAT=";
		//	std::cout << std::to_string(*static_cast<float*>(entry.data)).c_str();
		//	break;
		//}
		//case SyncType::BOOL:
		//{
		//	std::cout << "BOOL=";
		//	bool value = *static_cast<bool*>(entry.data);
		//	std::cout << (value ? "true" : "false");
		//	break;
		//}
		//case SyncType::STRING:
		//{
		//	std::cout << "STRING=";
		//	std::cout << static_cast<std::string*>(entry.data)->c_str();
		//	break;
		//}
		//default:
		//	std::cout << "ERROR ";
		//}

		std::cout << " size=" << entry.size << std::endl;
	}

	std::cout << "------------" << std::endl;
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

NetworkAdress NetworkServer::GetAddress() const
{
	return m_address;
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
	atexit(enet_deinitialize);
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
			Init();
			m_commands.pop();
			break;
		case CommandType::CONNECTTO:
			ConnectingTo(command.inputCharacter, command.inputInt);
			m_commands.pop();
			break;
		case CommandType::SENDMSGCLIENTS:
			SendMsgToClients(command.inputCharacter);
			m_commands.pop();
			break;
		case CommandType::SENDMSGSERVER:
			SendMsgToServer(command.inputCharacter);
			m_commands.pop();
			break;
		case CommandType::PRINTINFO:
			PrinNetworkInfos();
			m_commands.pop();
			break;
		case CommandType::CLOSE:
			Close();
			m_commands.pop();
			break;
		}
	}
}