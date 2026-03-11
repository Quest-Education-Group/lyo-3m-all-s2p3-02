#ifndef FOUNDRY_NODENETWORK__H_
#define FOUNDRY_NODENETWORK__H_

#include "Node.h"
#include "Servers/NetworkServer.h"

enum class NetworkType 
{
	CLIENT,
	SERVER
};

class NodeNetwork : public Node
{
public:
	NodeNetwork(std::string const& name);
	~NodeNetwork() override = default;

	virtual void OnUpdate(double delta) override;

	void InitNetworkFor(NetworkType type, int port = 0);
	void ConnectTo(const char* addressIP, int addressPort);
	void CloseNetwork();
	void PrintNetworkInfos();
	void SendMsgToServerInput();
	void SendMsgToServer(const char* message);
	void SendMsgToClients(const char* message);

	NetworkServer& GetNetwork() { return m_network; };
	std::string GetLocalIP() const { return m_network.GetLocalIP(); };

protected:

private:

	NetworkServer m_network;
};

#endif