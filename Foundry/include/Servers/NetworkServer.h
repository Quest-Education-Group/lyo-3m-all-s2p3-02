#ifndef FOUNDRY_NETWORKSERVER__H_
#define FOUNDRY_NETWORKSERVER__H_

#include "Server.hpp"
#include "Node.h"

#include <enet/enet.h>
#include <unordered_map>
#include <string>

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

enum class NetworkType
{
	CLIENT,
	SERVER,
};

struct Package
{
	char name[20] = {};
	uint32 nameSize = 0;
    byte data[255] = {};
	uint32 dataSize = 0;
};

template <>
struct Command<class NetworkServer>
{
	enum class CmdType { RECEIVE } Type;
	uptr<Package> pPackage;
};

using SyncRegistry = std::unordered_map<std::string, struct ISyncVar*>;

class NetworkServer : public Server<NetworkServer>
{
public:
	using CommandType = Command<NetworkServer>::CmdType;

	NetworkServer() = default;
	~NetworkServer() = default;

	void OnInitialize() override;
	void OnUnInitialize() override;

	static void Initialize() { Instance().OnInitialize(); }
	static void UnInitialize() { Instance().OnUnInitialize(); }

	static void ReceivePackage(uptr<Package>& package);
	static void SendPackage(Package const& package);

	static std::string GetLocalIP();
	static SyncRegistry& GetRegistry() { return Instance().m_registry; }

	static ENetHost*& GetEnetHost() { return Instance().m_pHost; }

protected:
	SyncRegistry m_registry {};
	ENetHost* m_pHost = nullptr;
	bool m_needFlushing = false;

private:
	bool StartEnet();
	void StopEnet();
	void BuildTasksImpl(TaskGraph& graph) override;
	void FlushCommandsImpl() override;

	void Command_ReceiveVar(uptr<Package>& package);
};

#endif