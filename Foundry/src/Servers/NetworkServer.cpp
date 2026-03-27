#include "Servers/NetworkServer.h"

#include "Debug.h"
#include "Logger.hpp"
#include "Network/SyncVar.h"

void NetworkServer::OnInitialize() { StartEnet(); }
void NetworkServer::OnUnInitialize() { StopEnet(); }

bool NetworkServer::StartEnet()
{
	if (enet_initialize() != 0)
	{
		Logger::LogWithLevel(LogLevel::ERROR, "An error occurred while initializing ENet.");
		return false;
	}

	Logger::Log("Enet Initialized");
	return true;

}

void NetworkServer::StopEnet()
{
	Logger::Log("Enet Program stopping");
	enet_deinitialize();
}

void NetworkServer::BuildTasksImpl(TaskGraph& graph) {}

void NetworkServer::FlushCommandsImpl()
{
	while (m_commands.empty() == false)
	{
		auto& [Type, pPackage] = m_commands.front();

		switch (Type)
		{
		case CommandType::RECEIVE:
			Command_ReceiveVar(pPackage);
			break;
		}

		m_commands.pop();
	}

	if (m_needFlushing) enet_host_flush(m_pHost);
	m_needFlushing = false;
}

void NetworkServer::Command_ReceiveVar(uptr<Package>& package)
{
	DEBUG("Receiving syncVars..." << std::endl);

	if (m_registry.contains(std::string(package->name)) == false)
		return;

	std::string pkgName;
	pkgName.resize(package->nameSize);
	std::memcpy(pkgName.data(), package->name, package->nameSize);

	if (m_registry[pkgName]->GetDirection() == SyncVarDirection::SEND_ONLY) return;
	std::memcpy(m_registry[pkgName]->Data(), package->data, package->dataSize);

	m_registry[pkgName]->ValueChanged();
}

void NetworkServer::ReceivePackage(uptr<Package>& package)
{
	Instance().m_commands.push({CommandType::RECEIVE, std::move(package)});
}

void NetworkServer::SendPackage(Package const& package)
{
	NetworkServer& instance = Instance();
	if (instance.m_pHost == nullptr) return;

	DEBUG("Sending SyncVars." << std::endl);
	ENetPacket* packet = enet_packet_create(&package, sizeof(Package), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(instance.m_pHost, 0, packet);

	instance.m_needFlushing = true;
}

std::string NetworkServer::GetLocalIP()
{
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0)
		return "127.0.0.1";

	addrinfo hints{};
	hints.ai_family = AF_INET;

	addrinfo* result = nullptr;

	int res = getaddrinfo(hostname, NULL, &hints, &result);
	if (res != 0 || result == nullptr)
		return "127.0.0.1";

	char ip[INET_ADDRSTRLEN] = { 0 };

	sockaddr_in* sockaddr_ipv4 = (sockaddr_in*)result->ai_addr;
	inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ip, sizeof(ip));

	freeaddrinfo(result);

	return std::string(ip);
}