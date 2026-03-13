#ifndef FOUNDRY_NODENETWORK__H_
#define FOUNDRY_NODENETWORK__H_

#include "Node.h"
#include "Servers/NetworkServer.h"

class NodeNetwork : public Node
{
public:
	NodeNetwork(std::string const& name);
	~NodeNetwork() override = default;

	virtual void OnUpdate(double delta) override;

	void InitNetworkFor(NetworkType type, int port = 0);
	void Start();
	void ConnectTo(const char* addressIP, int addressPort);
	void CloseNetwork();
	void SendMsgToServerInput();

	NetworkServer& GetNetwork() { return m_network; };
	std::string GetLocalIP() const { return m_network.GetLocalIP(); };
	bool GetIsRunning() const { return m_network.GetIsRunning(); };

protected:

private:
	// TODO : Remove that to only use instance
	NetworkServer m_network;
};

#endif