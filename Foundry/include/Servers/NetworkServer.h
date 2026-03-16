#ifndef FOUNDRY_NETWORKSERVER__H_
#define FOUNDRY_NETWORKSERVER__H_

#include "Server.hpp"
#include "Node.h"

#include <enet/enet.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <iostream>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>
#include <thread>

class NetworkServer;

enum class NetworkType
{
	CLIENT,
	SERVER,

	NOT_DEFINED
};

struct NetworkAdress
{
	uint32 host = 0;
	uint16 port = 0;
};

struct Package
{
	char name[20] = {};
	int32 size = 0;
    int8 data[255] = {};
};

struct SyncRegistry
{
	static SyncRegistry& Instance()
	{
		static SyncRegistry instance;
		return instance;
	}

	void Register(const std::string& name, const Package& entry)
	{
		m_registry.insert_or_assign(name, entry);
	}

	void Unregister(const std::string& name)
	{
		m_registry.erase(name);
	}

	std::unordered_map<std::string, Package>& Get()
	{
		return m_registry;
	}

private:
	std::unordered_map<std::string, Package> m_registry;
};

template <typename T, const char* Name>
struct Syncvar
{
public:
	Syncvar(const T& data) : m_Data(data)
	{
		Package entry;
		entry.size = sizeof(T);
		std::memcpy(entry.data, &m_Data, sizeof(T));

		SyncRegistry::Instance().Register(Name, entry);
	}

	~Syncvar()
	{
		SyncRegistry::Instance().Unregister(Name);
	}


	Syncvar& operator=(const T& other)
	{
		if (m_Data != other)
		{
			m_Data = other;
			//NetworkServer::SendSyncVar(); need thinking
		}

		return *this;
	}

	int Size() const
	{
		return sizeof(T);
	}

	const void* Data() const
	{
		return &m_Data;
	}

protected:

private:
	T m_Data;
	const char* m_name = Name;
};

//#define SyncVar(type, name) static const char __name__[] = name; Syncvar<type, __name__>
#define CONCAT_IMPL(x,y) x##y
#define CONCAT(x,y) CONCAT_IMPL(x,y)

#define SyncVar(type, name) \
static const char CONCAT(__name__, __LINE__)[] = name; \
Syncvar<type, CONCAT(__name__, __LINE__)>

template <>
struct Command<class NetworkServer>
{
	enum class CmdType { INIT, START, CLOSE, CONNECTTO, SENDMSGCLIENTS, SENDMSGSERVER, PRINTINFO } Type;
	const char* inputChar;
	int32 inputInt;
	int32 inputPort;
	NetworkType inputType;
};
using CommandType = Command<NetworkServer>::CmdType;

class NetworkServer : public Server<NetworkServer>
{
public:
	NetworkServer() = default;

	static bool Init(NetworkType networkType = NetworkType::NOT_DEFINED, int serverPort = 0);

	static void Start();
	static void Close();

	static bool ConnectingTo(const char* addressIP, int addressPort);

	static bool SendMsgToClientsInput();
	static bool SendMsgToServerInput();

	void Loop();
	void ReceiveConnection(ENetEvent& event);
	void ReceiveDisconnection(ENetEvent& event);
	void ReceivePackage(ENetEvent& event);

	void DisconnectFromServer();

	bool SendMsgToClients(const char* message);
	bool SendMsgToServer(const char* message);

	void CommandManager(std::string command);
	void PrinNetworkInfos();

	void ReceiveSyncVar(Package* package);
	void SendSyncVar(std::string const& name);
	void PrintSyncVar();
	void PrintSyncVarValues();
	
	std::string GetLocalIP() const;
	std::string TypeToStr() const;
	NetworkAdress GetAddress() const;
	bool GetIsRunning() const;
	NetworkType GetType() const;

	static bool StartEnet();
	static void StopEnet();

protected:
	NetworkAdress m_address = {};

	ENetHost* m_pHost = nullptr;
	ENetPeer* m_pServerConnection = nullptr;
	std::vector<ENetPeer*> m_clients;

private:
	NetworkType m_type = NetworkType::NOT_DEFINED;
	bool m_isRunning = false;

	void BuildTasksImpl(TaskGraph& graph) override;
	void FlushCommandsImpl() override;

	bool Command_Init(NetworkType networkType, int serverPort);
	void Command_Start();
	void Command_Close();
	bool Command_ConnectingTo(const char* addressIP, int addressPort);
	bool Command_SendMsgToClientsInput();
	bool Command_SendMsgToServerInput();
};

#endif